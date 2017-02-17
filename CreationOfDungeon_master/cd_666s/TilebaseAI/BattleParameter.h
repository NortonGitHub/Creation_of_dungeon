#pragma once
class BattleParameter
{
public:
    BattleParameter(int hp, int attack, int defence, int magicAttack, int magicDefence, int speed);
    ~BattleParameter();

    int _maxHP;
    int _hp;
    int _attack;
    int _defence;
    int _magicAttack;
    int _magicDefence;
    int _speed;

    const BattleParameter operator+(const BattleParameter& param);
    const BattleParameter operator+=(const BattleParameter& param);
    const BattleParameter operator-(const BattleParameter& param);
    const BattleParameter operator-=(const BattleParameter& param);
};

