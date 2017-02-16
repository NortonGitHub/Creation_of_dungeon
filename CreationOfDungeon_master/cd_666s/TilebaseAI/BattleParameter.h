#pragma once
class BattleParameter
{
public:
    BattleParameter(int hp, int mp, int attack, int defence, int speed);
    ~BattleParameter();

    int _maxHP;
    int _hp;
    int _attack;
    int _defence;
    int _speed;

    int _maxMP;
    int _mp;

    const BattleParameter operator+(const BattleParameter& param);
    const BattleParameter operator+=(const BattleParameter& param);
    const BattleParameter operator-(const BattleParameter& param);
    const BattleParameter operator-=(const BattleParameter& param);
};

