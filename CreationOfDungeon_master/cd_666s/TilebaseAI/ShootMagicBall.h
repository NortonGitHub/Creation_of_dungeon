#pragma once
#include "CharactersSkill.h"

class Character;

class ShootMagicBall : public CharactersSkill
{
public:
    ShootMagicBall(int cost, Character& chara, int range);
    ~ShootMagicBall();

    bool ShouldActivate() override;
    void Activate() override;

private:

    int _range;
    Character& _character;

};

