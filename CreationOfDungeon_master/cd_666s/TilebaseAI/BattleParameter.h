#pragma once
class BattleParameter
{
public:
    BattleParameter(int hp, int attack, int defence, int speed);
    ~BattleParameter();

    int _hp;
    int _attack;
    int _defence;
    int _speed;

    const BattleParameter operator+(const BattleParameter& param);
    const BattleParameter operator+=(const BattleParameter& param);
    const BattleParameter operator-(const BattleParameter& param);
    const BattleParameter operator-=(const BattleParameter& param);
};

