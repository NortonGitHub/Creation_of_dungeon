#pragma once
#include "TiledObject.h"

class MagicBall: public TiledObject
{
public:
    MagicBall(int power, int magicAttack, int range, TiledVector pos, TiledVector::Direction direction, TiledObject::Type type);
    ~MagicBall();

    void Update() override;
    bool IsOverwritable(TiledObject* overwriter) override;

private:

    int _range;
    int _magicAttack;
    int _power;

    double _speed;

    //���@���̈ړ�
    void Move();

    //���@�����G�Ƀq�b�g������
    void CheckHit();

    Vector2D _moveVec;

    TiledObject::Type _shooterType;
};

