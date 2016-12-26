#ifndef Dungeon_h
#define Dungeon_h

#include <string>
#include "MonsterController.h"
#include "TiledVector.h"
#include "ColleagueNotifyer.h"
#include "ObjectInformationDrawer.h"
#include "../../Vector2D.h"
#include "../Render/Sprite.h"

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
    
    //ƒQ[ƒ€ŠÔ
    long _currentWaveInterval;
    long _count;

    //—EÒ‚ğ’Ê‚µ‚Ä‚à‚¢‚¢”
    int _permitivePassedNum;
    
    std::string _stageName;
    
    void GenerateObject(std::string typeName, int countX, int countY);
    
    //“¯–¿ŠÔ‚Ìî•ñ‹¤—L–Ô
    ColleagueNotifyer _enemys, _monsters;
    
    ObjectInformationDrawer _infoDrawer;
    MonsterController _controller;
    Goal* _goal;
    StartPoint* _start;

    // MEMO : debug—p
    Sprite _face, _messageUI, _mainsFrame, _background;
};

#endif /* Dungeon_h */
