#pragma once
#include "TiledObject.h"
#include "../Resources/ImageResource.h"

class ShottenObject: public TiledObject
{
public:
    ShottenObject(int power, int attack, int range, double speed, TiledVector startPos, TiledVector::Direction direction, TiledObject::Type type, std::shared_ptr<ImageResource> image, bool isPhysical);
    ~ShottenObject();

    void Update() override;
    bool IsOverwritable(TiledObject* overwriter) override;

private:

    int _range;
    int _attack;
    int _power;

    bool _isPhysical;
    double _speed;

    //‰“‹——£UŒ‚‚ÌˆÚ“®
    void Move();

    //‰“‹——£UŒ‚‚ª“G‚Éƒqƒbƒg‚µ‚½‚©
    void CheckHit();

    Vector2D _moveVec;

    TiledObject::Type _shooterType;
};

