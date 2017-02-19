#pragma once
#include "CharactersSkill.h"
#include "ParameterMultiplier.h"

class Character;

class RiseParameter : public CharactersSkill
{
public:
    RiseParameter(ParameterMultiplier multiplier, int cost, Character& chara);
    ~RiseParameter();

    bool ShouldActivate() override;
    void Activate() override;

private:

    Character& _chara;
    ParameterMultiplier _multiplier;
};

