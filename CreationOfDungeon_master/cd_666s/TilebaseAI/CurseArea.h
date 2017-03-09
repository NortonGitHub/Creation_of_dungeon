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

    //パラメータ変動値
    ParameterMultiplier _multiplier;

    mutable Enemy* _targetCache;
};

