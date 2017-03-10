#include <array>
#include "../Utility/CSVReader.h"
#include "../Resources/AllResourceManager.h"

#include "StartPoint.h"
#include "Goal.h"
#include "Enemy.h"
#include "Monster.h"

#include "ShootMagicBall.h"
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

    if (name == "ghost")
    {
        auto cost = std::stoi(LoadLabeledElem("cost:", skillData));
        auto paramValue = std::stoi(LoadLabeledElem("param:", skillData));
        auto timeSec = std::stod(LoadLabeledElem("time:", skillData));
        auto time = static_cast<int>(timeSec * 60);
        BattleParameter percentParam(100, 100, paramValue, 100, paramValue, 100);
        ParameterMultiplier param(percentParam, time, true);
        return std::make_unique<RiseParameter>(std::move(param), cost, *this);
    }

    if (name == "minotaur")
    {
        auto cost = std::stoi(LoadLabeledElem("cost:", skillData));
        auto paramValue = std::stoi(LoadLabeledElem("param:", skillData));
        auto timeSec = std::stod(LoadLabeledElem("time:", skillData));
        auto time = static_cast<int>(timeSec * 60);
        BattleParameter percentParam(100, paramValue, 100, 100, 100, 100);
        ParameterMultiplier param(percentParam, time, true);
        return std::make_unique<RiseParameter>(std::move(param), cost, *this);
    }
    /*
    if (name == "bone")
    {
        auto cost = std::stoi(LoadLabeledElem("cost:", skillData));
        auto param = std::stoi(LoadLabeledElem("param:", skillData));
        auto timeSec = std::stod(LoadLabeledElem("time:", skillData));
        auto time = static_cast<int>(timeSec * 60);
        BattleParameter percentParam(100, param, 100, 100, 100, 100);
        ParameterMultiplier param(percentParam, time, true);
        return std::make_unique<ShootMagicBall>(100, 120, *this, 3);
    }
    */

    return nullptr;
}


CharactersSkill* CharactersSkill::CreateSkill(std::string skillData, Character& chara)
{
    if (skillData.find("") == std::string::npos)
        return nullptr;

    if (skillData.find("null") != std::string::npos)
        return nullptr;


    if (skillData.find("magic_attack#1") != std::string::npos)
        return new ShootMagicBall(100, 120, chara, 3);

    if (skillData.find("magic_attack#2") != std::string::npos)
        return new MagicAttackAround(120, 180, chara, 1);

    if (skillData.find("magic_attack#3") != std::string::npos)
        return new ShootMagicBall(150, 120, chara, 5);

    if (skillData.find("magic_attack#4") != std::string::npos)
        return new MagicAttackAround(200, 180, chara, 2);

    if (skillData.find("magic_attack#5") != std::string::npos)
        return new ShootMagicBall(250, 120, chara, 5);



    if (skillData.find("magic_heal#1") != std::string::npos)
        return new MagicHeal(0.5, 180, chara, 3);

    if (skillData.find("magic_heal#2") != std::string::npos)
        return new MagicHealAround(0.25, 180, chara, 5);

    if (skillData.find("magic_heal#3") != std::string::npos)
        return new MagicHeal(0.8, 180, chara, 5);

    if (skillData.find("magic_heal#4") != std::string::npos)
        return new MagicHealAround(0.5, 180, chara, 8);

    if (skillData.find("magic_heal#5") != std::string::npos)
        return new MagicHealAround(0.8, 180, chara, 10);



    if (skillData.find("param_rise#1") != std::string::npos)
    {
        BattleParameter percentParam(100, 125, 100, 100, 100, 100);
        ParameterMultiplier param(percentParam, 300, true);
        return new RiseParameter(std::move(param), 100, chara);
    }

    return nullptr;
}


void Trap::CreateTrap(std::string typeName, int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects)
{
    auto tilePos = TiledVector(countX, countY);

    if (typeName.find("name:mine") != std::string::npos)
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
    int cost = std::stoi(LoadLabeledElem("cost:", data));
    int range = std::stoi(LoadLabeledElem("range:", data));
    int power = std::stoi(LoadLabeledElem("power:", data));
    int attack = std::stoi(LoadLabeledElem("attack:", data));
    double stuckTimeSec = std::stod(LoadLabeledElem("stuck:", data)); // MEMO : 秒単位で設定させるため
    int stuckTime = static_cast<int>(stuckTimeSec * 60.0);

    return std::make_shared<MineBomb>(pos, cost, range, power, attack, stuckTime);
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
