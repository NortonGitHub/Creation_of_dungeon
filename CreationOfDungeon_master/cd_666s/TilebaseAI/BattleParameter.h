#pragma once
class BattleParameter
{
public:
	BattleParameter();
	BattleParameter(int hp, int attack, int defence, int magicAttack, int magicDefence, int speed, int lv);
    BattleParameter(int hp, int attack, int defence, int magicAttack, int magicDefence, int speed);
    ~BattleParameter();

    int _maxHP;
    int _hp;
    int _attack;
    int _defence;
    int _magicAttack;
    int _magicDefence;
    int _speed;
	int _level;

    const BattleParameter operator+(const BattleParameter& param);
    const BattleParameter operator+=(const BattleParameter& param);
    const BattleParameter operator-(const BattleParameter& param);
    const BattleParameter operator-=(const BattleParameter& param);
};

