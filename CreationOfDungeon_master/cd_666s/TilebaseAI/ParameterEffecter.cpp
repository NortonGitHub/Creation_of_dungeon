#include "ParameterEffecter.h"



ParameterEffecter::ParameterEffecter(int continuousTime, bool isPositive)
    : _time(0)
    , _affectionTime(continuousTime)
    , _isPositive(isPositive)
{
    if (_affectionTime <= 0)
        _affectionTime = 1;
}


ParameterEffecter::~ParameterEffecter()
{
}


void ParameterEffecter::UpdateCounter()
{
    if (_time < _affectionTime)
        _time++;
}
