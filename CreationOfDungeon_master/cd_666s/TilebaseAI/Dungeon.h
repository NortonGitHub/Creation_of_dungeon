#ifndef Dungeon_h
#define Dungeon_h

#include <string>
#include "MonsterController.h"
#include "TiledVector.h"
#include "ColleagueNotifyer.h"
#include "ObjectInformationDrawer.h"
#include "IntruderInfomation.h"
#include "DungeonTimer.h"
#include "../../Vector2D.h"
#include "../Render/Sprite.h"
#include "../Sound/Sound.h"

class GraphicalObject;
class TiledObject;
class Sprite;
class Sound;
class Action;
class Goal;
class StartPoint;

class Dungeon
{
public:
    Dungeon(std::string stageName);
    ~Dungeon();
    
    //void InitWithLoad(std::string stageName);
    void Init();
    void Clear();
    void Update();
    void Draw();

    bool HasClear();
    bool HasGameOver();
    
private:
    
    //ゲーム時間と時間通知モジュール群
    DungeonTimer _timer;

    //勇者を通してもいい数
    int _permitivePassedNum;
    
    std::string _stageName;
    
    void GenerateObject(std::string typeName, int countX, int countY);
    
    //同盟間の情報共有網
    ColleagueNotifyer _enemys, _monsters;
    
    //開始点と終了地点はグローバルなレベルでインスタンス生成しておく
    std::shared_ptr<Goal> _goal;
    std::shared_ptr<StartPoint> _start;

    //モンスター操作モジュール
    MonsterController _controller;

    //選択したモンスターの情報
    ObjectInformationDrawer _infoDrawer;

    //次に侵入してくるモンスターの情報
    IntruderInfomation _intruderInformation;

    // MEMO : debug用
    Sprite _face, _messageUI, _mainsFrame, _background, _windowBackground, _waveInfomartionBoard;
    //std::vector<Sprite*> _icons;
};

#endif /* Dungeon_h */
