#pragma once
#include "CharactersSkill.h"
#include "../Resources/ResourceManager.h"

class Character;

class MagicAttackAround : public CharactersSkill
{
public:
    MagicAttackAround(double power, int cost, double startRatio, int range, Character& chara);
    ~MagicAttackAround();

    bool ShouldActivate() override;
    void Activate() override;

    static std::unique_ptr<MagicAttackAround> Create(std::string data, Character& chara);

private:

    int _range;
    double _power;

    Character& _character;
    std::shared_ptr<ImageResource> _image;
};

