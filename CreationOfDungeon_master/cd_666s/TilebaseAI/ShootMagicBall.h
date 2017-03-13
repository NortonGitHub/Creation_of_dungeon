#pragma once
#include "CharactersSkill.h"
#include "../Resources/ResourceManager.h"

class Character;

class ShootMagicBall : public CharactersSkill
{
public:
    ShootMagicBall(double power, int cost, double speed, int range, Character& chara, bool isPhysical);
    ~ShootMagicBall();

    bool ShouldActivate() override;
    void Activate() override;

    static std::unique_ptr<ShootMagicBall> Create(std::string data, Character& chara, bool isPhysical);

    void SetImage(std::shared_ptr<ImageResource> image) { _image = image; };

private:

    std::shared_ptr<ImageResource> _image;

    double _speed;
    double _power;
    int _range;
    bool _isPhysical;
    Character& _character;
};

