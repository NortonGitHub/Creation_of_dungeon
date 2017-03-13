#pragma once
#include "TiledObject.h"
#include "../Resources/ImageResource.h"

class MagicBall: public TiledObject
{
public:
    MagicBall(int power, int attack, int range, double speed, TiledVector startPos, TiledVector::Direction direction, TiledObject::Type type, std::shared_ptr<ImageResource> image, bool isPhysical);
    ~MagicBall();

    void Update() override;
    bool IsOverwritable(TiledObject* overwriter) override;

private:

    int _range;
    int _attack;
    int _power;

    bool _isPhysical;
    double _speed;

    //�������U���̈ړ�
    void Move();

    //�������U�����G�Ƀq�b�g������
    void CheckHit();

    Vector2D _moveVec;

    TiledObject::Type _shooterType;
};

