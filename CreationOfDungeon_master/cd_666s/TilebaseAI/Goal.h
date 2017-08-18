#ifndef Goal_h
#define Goal_h

#include "TiledObject.h"
#include "MessageReciever.h"

class Character;
class ColleagueNotifyer;

class Goal : public TiledObject
{
public:
    Goal(TiledVector tilePos, ColleagueNotifyer& notifyer, MessageReciever& reciever, int permitivePassedNum);
    Goal(TiledVector tilePos, ColleagueNotifyer& notifyer);
    ~Goal();
    
    bool IsOverwritable(TiledObject* overwriter) override;

    void Init() override;
    void Update() override;
    void Draw() override;
    void Interact(Character& chara) override;
    
    //通過してしまった数を返す(これでGameOver判定できる)
    int GetPassedNum() const { return _passedNum; }
    
private:
    
    //同系列のキャラ間で情報共有するための通信機
    ColleagueNotifyer& _notifyer;

    MessageReciever& _reciever;
    TalkDatabase _tdb;
    
    int _passedNum;
    int _permitivePassedNum;
};

#endif /* Goal_h */
