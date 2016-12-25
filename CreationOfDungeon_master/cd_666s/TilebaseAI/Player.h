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

    //à”évåàíË
    virtual void Think() override;
    
    //à”évêãçs
    virtual void Act() override;
    
    void MoveToNext(TiledVector offset);
    
    int _time;
    int _updateInterval;
    TiledVector _beforeTilePos;
};

