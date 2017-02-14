#include "BattleParameter.h"
#include <algorithm>

BattleParameter::BattleParameter(int hp, int attack, int defence, int speed)
    : _hp(hp)
    , _attack(attack)
    , _defence(defence)
    , _speed(speed)
{
}


BattleParameter::~BattleParameter()
{
}



const BattleParameter BattleParameter::operator+(const BattleParameter& param)
{
    BattleParameter retParam(_hp, _attack, _defence, _speed);
    retParam._hp += param._hp;
    retParam._attack += param._attack;
    retParam._defence += param._defence;
    retParam._speed += param._speed;

    return std::move(retParam);
}


const BattleParameter BattleParameter::operator+=(const BattleParameter& param)
{
    _hp += param._hp;
    _attack += param._attack;
    _defence += param._defence;
    _speed += param._speed;

    return *this;
}


const BattleParameter BattleParameter::operator-(const BattleParameter& param)
{
    BattleParameter retParam(_hp, _attack, _defence, _speed);

    retParam._hp -= param._hp;
    if (retParam._hp < 0)
        retParam._hp = 0;

    retParam._attack -= param._attack;
    if (retParam._attack < 0)
        retParam._attack = 0;

    retParam._defence -= param._defence;
    if (retParam._defence < 0)
        retParam._defence = 0;

    retParam._speed -= param._speed;
    if (retParam._speed < 0)
        retParam._speed = 0;

    return std::move(retParam);
}


const BattleParameter BattleParameter::operator-=(const BattleParameter& param)
{
    _hp -= param._hp;
    if (_hp < 0)
        _hp = 0;

    _attack -= param._attack;
    if (_attack < 0)
        _attack = 0;

    _defence -= param._defence;
    if (_defence < 0)
        _defence = 0;

    _speed -= param._speed;
    if (_speed < 0)
        _speed = 0;

    return *this;
}