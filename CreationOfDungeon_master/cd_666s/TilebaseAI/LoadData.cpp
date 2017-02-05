#include <array>
#include "../Utility/CSVReader.h"
#include "../Resources/AllResourceManager.h"

#include "StartPoint.h"
#include "Goal.h"
#include "Enemy.h"
#include "Monster.h"


void Enemy::LoadEnemys(std::vector<std::shared_ptr<TiledObject>>& objects, StartPoint& start, Goal& goal, ColleagueNotifyer& notifyer, std::string fileName)
{
    _defeatedNum = 0;
    _enemysNum = 0;

    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray, 1);

    const int parameterNum = 6;
    std::array<int, parameterNum> params = { 0, 0, 0, 0, 0, 0 };
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
            //戦闘データ設定
            BattleParameter param = { params[0], params[1], params[2], params[3] };
            auto str = data.substr(1, data.size());
            auto enemy = std::make_shared<Enemy>(start.GetTilePos(), param, goal, notifyer, str);
            objects.push_back(enemy);
            //出現時間を秒単位に変換して入場者リストに追加
            start.AddToAppearList(enemy, params[4] * 60);

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

    const int parameterNum = 7;
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
            BattleParameter param = { params[0], params[1], params[2], params[3] };
            TiledVector startPos(params[4], params[5]);

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