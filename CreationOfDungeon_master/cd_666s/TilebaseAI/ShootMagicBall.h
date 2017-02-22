#pragma once
#include "CharactersSkill.h"

class Character;

class ShootMagicBall : public CharactersSkill
{
public:
    ShootMagicBall(double power, int cost, Character& chara, int range);
    ~ShootMagicBall();

    bool ShouldActivate() override;
    void Activate() override;

private:

    double _power;
    int _range;
    Character& _character;
};

