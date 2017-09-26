#include <array>
#include "../Utility/CSVReader.h"
#include "../Resources/AllResourceManager.h"

#include "Dungeon.h"
#include "StartPoint.h"
#include "Goal.h"
#include "Enemy.h"
#include "Monster.h"

#include "ShootDamageObject.h"
#include "MagicAttackAround.h"
#include "RiseParameter.h"
#include "MagicHeal.h"
#include "MagicHealAround.h"

#include "MineBomb.h"
#include "CurseArea.h"
#include "MagicBomb.h"
#include "Sanctuary.h"
#include "Emplacement.h"


//ラベルを取り払い、ラベル後続の値を読み取る
std::string LoadLabeledElem(const std::string& label, const std::string& rawData)
{
    size_t it = rawData.find(label);
    std::string cutData = rawData.substr(it + label.length());

    size_t dataEnd = cutData.find("&");
    cutData = cutData.substr(0, dataEnd);
    return cutData;
}

template<class T>
std::string LoadLabeledElemIfFind(const std::string& label, const std::string& rawData, T fallback)
{
    size_t it = rawData.find(label);
    std::string cutData = rawData.substr(it + label.length());
    if (it == std::string::npos)
        return std::to_string(fallback);

    size_t dataEnd = cutData.find("&");
    cutData = cutData.substr(0, dataEnd);
    return cutData;
}

void Enemy::LoadEnemys(std::vector<std::shared_ptr<TiledObject>>& objects, StartPoint& start, Goal& goal, ColleagueNotifyer& notifyer, std::string fileName)
{
    _defeatedNum = 0;
    _enemysNum = 0;

    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray, 1);

    const int parameterNum = 9;
    std::array<int, parameterNum> params = { 0, 0, 0, 0, 0, 0, 0 };
    std::string name = "";
    std::string skillData = "";

    int idx = 0;
    int count = 0;
    for (auto data : dataArray)
    {
        if (data.empty()) {
            break;
        }

        // MEMO : 最後だけはファイル名をそのまま使う
        if (count < parameterNum - 2)
        {
            params[count] = std::stoi(data);
        }
        else if (count == parameterNum - 2)
        {
            name = data;
        }
        else
        {
            skillData = data;
        }

        count++;

        if (count == parameterNum)
        {
            //戦闘データ設定
            //hp, skillCost, atk, def, matk, mdef, speed
            BattleParameter param = { params[0], params[1], params[2], params[3], params[4], params[5]};

            auto enemy = std::make_shared<Enemy>(start.GetTilePos(), param, goal, notifyer, name);

            //スキル生成
            std::unique_ptr<CharactersSkill> skill(CharactersSkill::CreateSkill(skillData, *enemy));
            enemy->_skill = std::move(skill);

            objects.push_back(enemy);
            //出現時間を秒単位に変換して入場者リストに追加
            start.AddToAppearList(enemy, params[6] * 60);

            //次のキャラへ
            count = 0;
            idx++;

            _enemysNum++;
        }
    }
}


void Dungeon::LoadTileSize(std::string stageName, std::vector<std::string>& rawData)
{
    auto stageNum = std::stoi(stageName);
    auto tileSize = rawData[stageNum * 2 - 1];

    if (tileSize == "large")
        TILE_SIZE = 48;
    else if (tileSize == "midium")
        TILE_SIZE = 40;
    else
        TILE_SIZE = 32;
}


void Monster::LoadMonsters(std::vector<std::shared_ptr<TiledObject>>& objects, ColleagueNotifyer& notifyer, std::string fileName)
{
    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray, 1);

    const int parameterNum = 10;
    std::array<int, parameterNum> params = { 0, 0, 0, 0, 0, 0, 0 };
    int idx = 0;
    int count = 0;
    std::string name;
    std::string skill;
    for (auto data : dataArray)
    {
        if (data.empty()) {
            break;
        }

        // MEMO : 最後だけはファイル名をそのまま使う
        if (count < parameterNum - 2)
            params[count] = std::stoi(data);
        else if (count == parameterNum - 2)
            name = data;
        else if (count == parameterNum - 1)
            skill = data;

        count++;

        if (count == parameterNum)
        {
            BattleParameter param = { params[0], params[1], params[2], params[3], params[4], params[5] };
            TiledVector startPos(params[6], params[7]);

            auto monster = std::make_shared<Monster>(startPos, param, nullptr, notifyer, name, skill);
            objects.push_back(monster);

            auto magicSquare = std::make_shared<MagicSquare>(startPos, *monster);
            monster->_home = magicSquare.get();
            objects.push_back(magicSquare);

            //次のキャラへ
            count = 0;
            idx++;
        }
    }
}


std::unique_ptr<CharactersSkill> Monster::CreateSkillFromName(std::string name, std::string skillData)
{
    if (skillData == "")
        return nullptr;
    if (skillData == "null")
        return nullptr;

    if (name == "slime")
    {
        auto cost = std::stoi(LoadLabeledElem("cost:", skillData));
        auto paramValue = std::stoi(LoadLabeledElem("param:", skillData));
        auto timeSec = std::stod(LoadLabeledElem("time:", skillData));
        auto time = static_cast<int>(timeSec * 60);

        //百分率に変換
        double startMPRatio = std::stoi(LoadLabeledElemIfFind("mpRatio:", skillData, 0.0));
        startMPRatio /= 100;

        BattleParameter percentParam(100, 100, paramValue, 100, paramValue, 100);
        ParameterMultiplier param(percentParam, time, true);
        return std::make_unique<RiseParameter>(std::move(param), cost, startMPRatio, *this);
    }

    if (name == "minotaur")
    {
        auto cost = std::stoi(LoadLabeledElem("cost:", skillData));
        auto paramValue = std::stoi(LoadLabeledElem("param:", skillData));
        auto timeSec = std::stod(LoadLabeledElem("time:", skillData));
        auto time = static_cast<int>(timeSec * 60);

        //百分率に変換
        double startMPRatio = std::stoi(LoadLabeledElemIfFind("mpRatio:", skillData, 0.0));
        startMPRatio /= 100;

        BattleParameter percentParam(100, paramValue, 100, 100, 100, 100);
        ParameterMultiplier param(percentParam, time, true);
        return std::make_unique<RiseParameter>(std::move(param), cost, startMPRatio, *this);
    }
    
    if (name == "bone")
    {
        auto skill = ShootDamageObject::Create(skillData, *this, true);
        skill->SetImage(IMAGE_RESOURCE_TABLE->Create("resource/graph/effect/throwing_bone.png"));
        return skill;
    }

    return nullptr;
}


std::unique_ptr<CharactersSkill> CharactersSkill::CreateSkill(std::string skillData, Character& chara)
{
    if (skillData == "")
        return nullptr;

    if (skillData == "null")
        return nullptr;

    if (skillData.find("shoot") != std::string::npos)
        return ShootDamageObject::Create(skillData, chara, true);

    if (skillData.find("magic_shoot") != std::string::npos)
        return ShootDamageObject::Create(skillData, chara, false);

    if (skillData.find("magic_explode") != std::string::npos)
        return MagicAttackAround::Create(skillData, chara);

    if (skillData.find("heal") != std::string::npos)
        return MagicHeal::Create(skillData, chara);

    if (skillData.find("heal_around") != std::string::npos)
        return MagicHealAround::Create(skillData, chara);

    if (skillData.find("param_rise") != std::string::npos)
        return RiseParameter::Create(skillData, chara);

    return nullptr;
}


std::unique_ptr<ShootDamageObject> ShootDamageObject::Create(std::string data, Character& chara, bool isPhysical)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));
    double power = std::stod(LoadLabeledElem("power:", data));
    double speed = std::stod(LoadLabeledElem("speed:", data));

    //百分率に変換
    double startMPRatio = std::stoi(LoadLabeledElemIfFind("mpRatio:", data, 0.0));
    startMPRatio /= 100;

    return std::make_unique<ShootDamageObject>(power, cost, startMPRatio, speed, range, chara, true);
}


std::unique_ptr<MagicAttackAround> MagicAttackAround::Create(std::string data, Character& chara)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));
    double power = std::stod(LoadLabeledElem("power:", data));

    //百分率に変換
    double startMPRatio = std::stoi(LoadLabeledElemIfFind("mpRatio:", data, 0.0));
    startMPRatio /= 100;

    return std::make_unique<MagicAttackAround>(power, cost, startMPRatio, range, chara);
}


std::unique_ptr<MagicHeal> MagicHeal::Create(std::string data, Character& chara)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));
    double power = std::stod(LoadLabeledElem("power:", data));

    //百分率に変換
    double startMPRatio = std::stoi(LoadLabeledElemIfFind("mpRatio:", data, 0.0));
    startMPRatio /= 100;

    return std::make_unique<MagicHeal>(power, cost, startMPRatio, range, chara);
}


std::unique_ptr<MagicHealAround> MagicHealAround::Create(std::string data, Character& chara)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));
    double power = std::stod(LoadLabeledElem("power:", data));

    //百分率に変換
    double startMPRatio = std::stoi(LoadLabeledElemIfFind("mpRatio:", data, 0.0));
    startMPRatio /= 100;

    return std::make_unique<MagicHealAround>(power, cost, startMPRatio, range, chara);
}


std::unique_ptr<RiseParameter> RiseParameter::Create(std::string data, Character& chara)
{
    auto cost = std::stoi(LoadLabeledElem("cost:", data));
    auto timeSec = std::stod(LoadLabeledElem("time:", data));
    auto time = static_cast<int>(timeSec * 60);

    int hp = std::stod(LoadLabeledElem("hp:", data));
    int atk = std::stod(LoadLabeledElem("atk:", data));
    int def = std::stod(LoadLabeledElem("def:", data));
    int matk = std::stod(LoadLabeledElem("matk:", data));
    int mdef = std::stod(LoadLabeledElem("mdef:", data));
    int spd = std::stoi(LoadLabeledElem("spd:", data));
    BattleParameter percentParam(hp, atk, def, matk, mdef, spd);

    //百分率に変換
    double startMPRatio = std::stoi(LoadLabeledElemIfFind("mpRatio:", data, 0.0));
    startMPRatio /= 100;

    ParameterMultiplier param(percentParam, time, true);
    return std::make_unique<RiseParameter>(std::move(param), cost, startMPRatio, chara);
}


void Trap::CreateTrap(std::string typeName, int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects)
{
    auto tilePos = TiledVector(countX, countY);

    if (typeName.find("name:mine") != std::string::npos
        || typeName.find("name:bare_trap") != std::string::npos)
    {
        objects.push_back(MineBomb::Create(typeName, tilePos));
        return;
    }
    if (typeName.find("name:magic_bomb") != std::string::npos)
    {
        objects.push_back(MagicBomb::Create(typeName, tilePos));
        return;
    }
    if (typeName.find("name:curse") != std::string::npos)
    {
        objects.push_back(CurseArea::Create(typeName, tilePos));
        return;
    }
    if (typeName.find("name:sanctuary") != std::string::npos)
    {
        objects.push_back(Sanctuary::Create(typeName, tilePos));
        return;
    }
    if (typeName.find("name:emplacement") != std::string::npos)
    {
        objects.push_back(Emplacement::Create(typeName, tilePos));
        return;
    }
}


std::shared_ptr<MineBomb> MineBomb::Create(std::string data, TiledVector pos)
{
    std::string name = LoadLabeledElem("name:", data);
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));
    int power = std::stoi(LoadLabeledElem("power:", data));
    int attack = std::stoi(LoadLabeledElem("attack:", data));
    double stuckTimeSec = std::stod(LoadLabeledElem("stuck:", data)); // MEMO : 秒単位で設定させるため
    int stuckTime = static_cast<int>(stuckTimeSec * 60.0);

    if (name == "mine")
        return std::make_shared<MineBomb>(pos, cost, range, power, attack, stuckTime, true);
    else
        return std::make_shared<MineBomb>(pos, cost, range, power, attack, stuckTime, false);
}


std::shared_ptr<MagicBomb> MagicBomb::Create(std::string data, TiledVector pos)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));
    int power = std::stoi(LoadLabeledElem("power:", data));
    int attack = std::stoi(LoadLabeledElem("attack:", data));

    return std::make_shared<MagicBomb>(pos, cost, range, power, attack);
}


std::shared_ptr<CurseArea> CurseArea::Create(std::string data, TiledVector pos)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int hp = std::stoi(LoadLabeledElem("hp:", data));
    int atk = std::stoi(LoadLabeledElem("atk:", data));
    int def = std::stoi(LoadLabeledElem("def:", data));
    int matk = std::stoi(LoadLabeledElem("matk:", data));
    int mdef = std::stoi(LoadLabeledElem("mdef:", data));
    int spd = std::stoi(LoadLabeledElem("spd:", data));

    double continuousTimeSec = std::stod(LoadLabeledElem("time:", data));
    int continuousTime = static_cast<int>(continuousTimeSec * 60.0);

    BattleParameter param(hp, atk, def, matk, mdef, spd);
    ParameterMultiplier multiplier(std::move(param), continuousTime, false);
    return std::make_shared<CurseArea>(pos, cost, std::move(multiplier));
}


std::shared_ptr<Sanctuary> Sanctuary::Create(std::string data, TiledVector pos)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));

    int hp = std::stoi(LoadLabeledElem("hp:", data));
    int atk = std::stoi(LoadLabeledElem("atk:", data));
    int def = std::stoi(LoadLabeledElem("def:", data));
    int matk = std::stoi(LoadLabeledElem("matk:", data));
    int mdef = std::stoi(LoadLabeledElem("mdef:", data));
    int spd = std::stoi(LoadLabeledElem("spd:", data));

    double continuousTimeSec = std::stod(LoadLabeledElem("time:", data));
    int continuousTime = static_cast<int>(continuousTimeSec * 60.0);

    BattleParameter param(hp, atk, def, matk, mdef, spd);
    ParameterMultiplier multiplier(std::move(param), continuousTime, true);

    return std::make_shared<Sanctuary>(pos, range, cost, std::move(multiplier));
}


std::shared_ptr<Emplacement> Emplacement::Create(std::string data, TiledVector pos)
{
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int power = std::stoi(LoadLabeledElem("power:", data));
    int attack = std::stoi(LoadLabeledElem("attack:", data));

    auto directionStr = LoadLabeledElem("direction:", data);
    auto direction = TiledVector::BACK;
    if (directionStr == "left")
        direction = TiledVector::LEFT;
    else if (directionStr == "right")
        direction = TiledVector::RIGHT;
    else if (directionStr == "down")
        direction = TiledVector::FORWARD;

    return std::make_shared<Emplacement>(pos, cost, power, attack, direction);
}



//敵を後から追加で生成する
std::vector<TiledObject*> Monster::GenerateMonster(std::vector<std::shared_ptr<TiledObject>>& objects, ColleagueNotifyer& notifyer, std::string fileName, TiledVector startPos,std::string* GenerateText)
{

    *GenerateText = "";

    std::vector<TiledObject*> monsterObjects;

    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray, 1);

    const int parameterNum = 8;
    std::array<int, parameterNum> params = { 0, 0, 0, 0, 0, 0, 0 };
    int idx = 0;
    int count = 0;
    std::string name;
    std::string skill;
    for (auto data : dataArray)
    {
        // MEMO : 最後だけはファイル名をそのまま使う
        if (count < parameterNum - 2)
            params[count] = std::stoi(data);
        else if (count == parameterNum - 2) {
            *GenerateText += std::to_string(startPos._x) + "," + std::to_string(startPos._y) + ",";
            name = data;
        }
        else if (count == parameterNum - 1)
            skill = data;

        count++;

        *GenerateText += data;

        if (count == parameterNum)
        {
            BattleParameter param = { params[0], params[1], params[2], params[3], params[4], params[5] };
            //TiledVector startPos(params[6], params[7]);

            auto monster = std::make_shared<Monster>(startPos, param, nullptr, notifyer, name, skill);
            objects.push_back(monster);

            auto magicSquare = std::make_shared<MagicSquare>(startPos, *monster);
            monster->_home = magicSquare.get();
            objects.push_back(magicSquare);

            monsterObjects.push_back(monster.get());
            monsterObjects.push_back(magicSquare.get());

            //次のキャラへ
            count = 0;
            idx++;
        }else{
            *GenerateText += ",";
        }
    }

    return monsterObjects;

}












