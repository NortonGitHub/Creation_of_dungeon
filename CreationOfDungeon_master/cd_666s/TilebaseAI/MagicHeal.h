#pragma once
#include "CharactersSkill.h"

class Character;


class MagicHeal : public CharactersSkill
{
public:
    MagicHeal(double power, int cost, double startRatio, int range, Character& chara);
    ~MagicHeal();

    bool ShouldActivate() override;
    void Activate() override;

    static std::unique_ptr<MagicHeal> Create(std::string data, Character& chara);

private:

    double _power;
    int _range;

    Character& _character;
    Character* _targetCache;
};

