#pragma once
#include "CharactersSkill.h"

class Character;

class MagicAttackAround : public CharactersSkill
{
public:
    MagicAttackAround(double power, int cost, Character& chara, int range);
    ~MagicAttackAround();

    bool ShouldActivate() override;
    void Activate() override;

private:

    double _power;
    int _range;
    Character& _character;
};

