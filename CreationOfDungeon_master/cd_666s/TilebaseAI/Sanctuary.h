#pragma once
#include "Trap.h"
#include "ParameterMultiplier.h"

class Sanctuary : public Trap
{
public:
    Sanctuary(TiledVector pos, int range, int cost, ParameterMultiplier multiplier);
    ~Sanctuary();

    void Activate() override;
    bool IsActivatable() const override;

private:

    //�����͈�
    int _range;

    //�p�����[�^�ϓ��l
    ParameterMultiplier _multiplier;
};

