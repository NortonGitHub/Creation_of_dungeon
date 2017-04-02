#include "RiseParameter.h"
#include "Character.h"

RiseParameter::RiseParameter(ParameterMultiplier multiplier, int cost, double startRatio, Character& chara)
    : CharactersSkill(cost, startRatio)
    , _chara(chara)
    , _multiplier(std::move(multiplier))
{
}


RiseParameter::~RiseParameter()
{
}


bool RiseParameter::ShouldActivate()
{
    return (_mp >= _mpCost);
}


void RiseParameter::Activate()
{
    if (_mp < _mpCost)
        return;

    _mp = 0;

    auto copy = std::make_unique<ParameterMultiplier>(_multiplier);
    _chara.AddParameterEffecter(std::move(copy));
}