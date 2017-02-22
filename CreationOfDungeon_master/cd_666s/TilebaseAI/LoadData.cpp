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

    const int parameterNum = 9;
    std::array<int, parameterNum> params = { 0, 0, 0, 0, 0, 0, 0 };
    int idx = 0;
    int count = 0;
    for (auto data : dataArray)
    {
        // MEMO : 最後だけはファイル名をそのまま使う
        if (count < parameterNum - 1)
            params[count] = std::stoi(data);

        count++;

        if (count == parameterNum)
        {
            BattleParameter param = { params[0], params[1], params[2], params[3], params[4], params[5] };
            TiledVector startPos(params[6], params[7]);

            auto str = data.substr(1, data.size());
            auto monster = std::make_shared<Monster>(startPos, param, nullptr, notifyer, str);
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


CharactersSkill* CharactersSkill::CreateSkill(std::string skillData, Character& chara)
{
    if (skillData.find("") == std::string::npos)
        return nullptr;

    if (skillData.find("null") != std::string::npos)
        return nullptr;


    if (skillData.find("magic_attack#1") != std::string::npos)
        return new ShootMagicBall(0.3, 120, chara, 3);

    if (skillData.find("magic_attack#2") != std::string::npos)
        return new MagicAttackAround(0.3, 180, chara, 1);

    if (skillData.find("magic_attack#3") != std::string::npos)
        return new ShootMagicBall(0.5, 120, chara, 5);

    if (skillData.find("magic_attack#4") != std::string::npos)
        return new MagicAttackAround(0.5, 180, chara, 2);

    if (skillData.find("magic_attack#5") != std::string::npos)
        return new ShootMagicBall(0.8, 120, chara, 5);



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