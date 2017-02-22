#pragma once
#include <vector>
#include "CharactersSkill.h"

class Character;

class MagicHealAround : public CharactersSkill
{
public:
    MagicHealAround(double power, int cost, Character& chara, int range);
    ~MagicHealAround();

    bool ShouldActivate() override;
    void Activate() override;

private:

    double _power;
    int _range;

    Character& _character;
    std::vector<Character*> _targetsCache;
};

