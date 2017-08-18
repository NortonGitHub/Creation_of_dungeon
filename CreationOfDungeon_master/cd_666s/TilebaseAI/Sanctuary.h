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

    static std::shared_ptr<Sanctuary> Create(std::string data, TiledVector pos);

private:

    //爆風範囲
    int _range;

    //パラメータ変動値
    ParameterMultiplier _multiplier;

    Sound _sound;
};

