#include <array>
#include "../Utility/CSVReader.h"
#include "../Resources/AllResourceManager.h"

#include "StartPoint.h"
#include "Goal.h"
#include "Enemy.h"
#include "Monster.h"
#include "ShootMagicBall.h"


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
        // MEMO : �Ōゾ���̓t�@�C���������̂܂܎g��
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
            //�퓬�f�[�^�ݒ�
            //hp, skillCost, atk, def, matk, mdef, speed
            BattleParameter param = { params[0], params[1], params[2], params[3], params[4], params[5]};

            auto enemy = std::make_shared<Enemy>(start.GetTilePos(), param, goal, notifyer, name);

            //�X�L������
            std::unique_ptr<CharactersSkill> skill(CharactersSkill::CreateSkill(skillData, *enemy));
            enemy->_skill = std::move(skill);

            objects.push_back(enemy);
            //�o�����Ԃ�b�P�ʂɕϊ����ē���҃��X�g�ɒǉ�
            start.AddToAppearList(enemy, params[6] * 60);

            //���̃L������
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
        // MEMO : �Ōゾ���̓t�@�C���������̂܂܎g��
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

            //���̃L������
            count = 0;
            idx++;
        }
    }
}


CharactersSkill* CharactersSkill::CreateSkill(std::string skillData, Character& chara)
{
    if (skillData.find("null") != std::string::npos)
        return nullptr;

    if (skillData.find("magic_ball") != std::string::npos)
        return new ShootMagicBall(180, chara, 3);

    return nullptr;
}