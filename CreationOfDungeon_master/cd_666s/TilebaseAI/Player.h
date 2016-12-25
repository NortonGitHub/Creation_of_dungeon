#pragma once
#include "Character.h"

class Player : public Character
{
public:
    Player(TiledVector pos, ColleagueNotifyer& notifyer);
    ~Player();

    void Update() override;
    void Draw() override;
    bool IsOverwritable(TiledObject* overwriter) override;

private:

    //�ӎv����
    virtual void Think() override;
    
    //�ӎv���s
    virtual void Act() override;
    
    void MoveToNext(TiledVector offset);
    
    int _time;
    int _updateInterval;
    TiledVector _beforeTilePos;
};

