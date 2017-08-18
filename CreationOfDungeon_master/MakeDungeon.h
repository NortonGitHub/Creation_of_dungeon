
#pragma once
#include "cd_666s\InputManager\MouseInput.h"
#include "cd_666s\TilebaseAI\MapTile.h"
#include "cd_666s/TilebaseAI/ColleagueNotifyer.h"

#include "cd_666s/TilebaseAI/Goal.h"
#include "cd_666s/TilebaseAI/StartPoint.h"

#include "UIManager.h"

class MakeDungeon
{
public:
    MakeDungeon();
    MakeDungeon(std::string stage_num);
    ~MakeDungeon();

    void Update();

    void Draw();

    void Init(std::string file_name);

    void PickupObject();

    void LoadTileSize(std::string stageName, std::vector<std::string>& rawData);

private:

    std::string _stage_num;

    void GenerateObject(std::string typeName, int countX, int countY);

    //開始点と終了地点はグローバルなレベルでインスタンス生成しておく
    std::shared_ptr<Goal> _goal;
    std::shared_ptr<StartPoint> _start;

    //同盟間の情報共有網
    ColleagueNotifyer _monsters,_enemys;

    //現在選ばれているオブジェクト
    std::string _selectingObj;

    Sprite _mainsFrame, _background, _windowBackground;

};

