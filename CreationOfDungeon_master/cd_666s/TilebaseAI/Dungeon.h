#ifndef Dungeon_h
#define Dungeon_h

#include <string>
#include "MonsterController.h"
#include "TiledVector.h"
#include "ColleagueNotifyer.h"
#include "ObjectInformationDrawer.h"
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
    
    //ゲーム時間
    long _currentWaveInterval;
    long _count;

    //勇者を通してもいい数
    int _permitivePassedNum;
    
    std::string _stageName;
    
    void GenerateObject(std::string typeName, int countX, int countY);
    
    //同盟間の情報共有網
    ColleagueNotifyer _enemys, _monsters;
    
    ObjectInformationDrawer _infoDrawer;
    MonsterController _controller;
    Goal* _goal;
    StartPoint* _start;

    Sound _halfSE, _littleSE, _endSE;

    // MEMO : debug用
    Sprite _face, _braver, _messageUI, _mainsFrame, _background, _windowBackground, _information;
};

#endif /* Dungeon_h */
