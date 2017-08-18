#pragma once
#include <string>
#include <memory>
#include "BattleParameter.h"

class Character;

class CharactersSkill
{
public:
    CharactersSkill(int cost, double startRatio = 0.0);
    virtual ~CharactersSkill();

    static std::unique_ptr<CharactersSkill> CreateSkill(std::string skillData, Character& charam);

    virtual bool ShouldActivate() { return true; }
    virtual void Activate() = 0;
    
    //MP’l‘€ì‚ÉŠÖ‚·‚éƒ‚ƒWƒ…[ƒ‹
    void Update();
    bool IsReadyToUse();

    int _mp;
    int _mpCost;
};

