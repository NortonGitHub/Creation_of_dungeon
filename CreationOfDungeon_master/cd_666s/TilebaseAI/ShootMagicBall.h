#pragma once
#include "CharactersSkill.h"
#include "../Resources/ResourceManager.h"

class Character;

class ShootMagicBall : public CharactersSkill
{
public:
    ShootMagicBall(double power, int cost, double speed, int range, Character& chara);
    ~ShootMagicBall();

    bool ShouldActivate() override;
    void Activate() override;

    static std::unique_ptr<ShootMagicBall> Create(std::string data, Character& chara);

private:

    std::shared_ptr<ImageResource> _image;

    double _speed;
    double _power;
    int _range;
    Character& _character;
};

