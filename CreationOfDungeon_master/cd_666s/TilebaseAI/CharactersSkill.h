#pragma once
#include "BattleParameter.h"

class CharactersSkill
{
public:
    CharactersSkill(BattleParameter& param);
    ~CharactersSkill();

    virtual bool ShouldActivate() { return true; }
    virtual void Activate() = 0;
    
    //MP�l����Ɋւ��郂�W���[��
    void Update();
    bool IsReadyToUse();
    BattleParameter& _param;
};

