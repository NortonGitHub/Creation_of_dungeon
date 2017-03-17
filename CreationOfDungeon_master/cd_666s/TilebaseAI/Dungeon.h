#ifndef Dungeon_h
#define Dungeon_h

#include <string>
#include <unordered_map>
#include "MonsterController.h"
#include "TiledVector.h"
#include "ColleagueNotifyer.h"
#include "ObjectInformationDrawer.h"
#include "IntruderInfomation.h"
#include "TiledObjectDictionary.h"
#include "DungeonTimer.h"
#include "MessageReciever.h"

#include "../Render/Sprite.h"
#include "../Sound/Sound.h"



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
    
    void LoadTileSize(std::string stageName, std::vector<std::string>& rawData);

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

    //アイコンと名前の対応表
    const TiledObjectDictionary _dictionary;

    //選択したモンスターの情報
    ObjectInformationDrawer _infoDrawer;

    //次に侵入してくるモンスターの情報
    IntruderInfomation _intruderInformation;

    //メッセージウィンドウ
    MessageReciever _messageReciever;

    // MEMO : debug用
    Sprite _mainsFrame, _background, _windowBackground, _waveInfomartionBoard;

    // MEMO : 突貫工事用
    void LoadMessage(std::string stageName);
    void UpdateSecretary();
    std::unordered_map<std::string, TalkDatabase> _dungeonMessage;
    bool _intrudeLastCharacter;
};

#endif /* Dungeon_h */
