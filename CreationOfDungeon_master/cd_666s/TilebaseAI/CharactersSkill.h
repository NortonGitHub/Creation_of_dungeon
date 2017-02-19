#pragma once
#include <string>
#include "BattleParameter.h"

class Character;

class CharactersSkill
{
public:
    CharactersSkill(int cost);
    ~CharactersSkill();

    //static CharactersSkill* CreateSkill(std::string skillData, Character& charam);
    static CharactersSkill* CreateSkill(std::string skillData, Character& charam);

    virtual bool ShouldActivate() { return true; }
    virtual void Activate() = 0;
    
    //MP値操作に関するモジュール
    void Update();
    bool IsReadyToUse();

    int _mp;
    int _mpCost;
};

