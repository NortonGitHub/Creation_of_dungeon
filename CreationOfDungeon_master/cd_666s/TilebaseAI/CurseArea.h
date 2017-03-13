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

    static std::shared_ptr<CurseArea> Create(std::string data, TiledVector pos);

private:

    //�p�����[�^�ϓ��l
    ParameterMultiplier _multiplier;

    mutable Enemy* _targetCache;
};
