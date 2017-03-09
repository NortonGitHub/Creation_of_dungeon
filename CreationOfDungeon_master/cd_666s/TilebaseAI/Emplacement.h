#pragma once
#include "Trap.h"

class Enemy;

class Emplacement : public Trap
{
public:
    Emplacement(TiledVector pos, int cost, int power, int attack, TiledVector::Direction direction);
    ~Emplacement();

    void Activate() override;
    bool IsActivatable() const override;

private:

    //�U����
    int _attack;

    //�З�
    int _power;

    //�U������
    TiledVector::Direction _shootDirection;
};

