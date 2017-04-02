#pragma once
#include <vector>
#include "CharactersSkill.h"

class Character;

class MagicHealAround : public CharactersSkill
{
public:
    MagicHealAround(double power, int cost, double startRatio, int range, Character& chara);
    ~MagicHealAround();

    bool ShouldActivate() override;
    void Activate() override;

    static std::unique_ptr<MagicHealAround> Create(std::string data, Character& chara);

private:

    double _power;
    int _range;

    Character& _character;
    std::vector<Character*> _targetsCache;
};

