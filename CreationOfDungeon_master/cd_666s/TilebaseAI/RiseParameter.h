#pragma once
#include "CharactersSkill.h"
#include "ParameterMultiplier.h"

class Character;

class RiseParameter : public CharactersSkill
{
public:
    RiseParameter(ParameterMultiplier multiplier, int cost, double startRatio, Character& chara);
    ~RiseParameter();

    bool ShouldActivate() override;
    void Activate() override;

    static std::unique_ptr<RiseParameter> Create(std::string data, Character& chara);

private:

    Character& _chara;
    ParameterMultiplier _multiplier;
};

