#pragma once
#include "Trap.h"
#include "ParameterMultiplier.h"

class Enemy;

class CurseArea : public Trap
{
public:
    CurseArea(TiledVector pos, int cost, ParameterMultiplier multiplier);
    ~CurseArea();

    void Activate() override;
    bool IsActivatable() const override;

private:

    //�p�����[�^�ϓ��l
    ParameterMultiplier _multiplier;

    mutable Enemy* _targetCache;
};

