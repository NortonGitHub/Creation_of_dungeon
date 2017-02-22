#pragma once
#include "CharactersSkill.h"

class Character;


class MagicHeal : public CharactersSkill
{
public:
    MagicHeal(double power, int cost, Character& chara, int range);
    ~MagicHeal();

    bool ShouldActivate() override;
    void Activate() override;

private:

    double _power;
    int _range;

    Character& _character;
    Character* _targetCache;
};

