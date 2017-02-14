#pragma once
#include "BattleParameter.h"

class Equipment
{
public:

    Equipment(BattleParameter bonusParam, int goldValue);
    ~Equipment();

    BattleParameter GetBonusParam() const { return _bonusParameter; }
    int GetGoldValue() const { return _goldValue; };

    //const static Equipment _empty;

private:

    BattleParameter _bonusParameter;
    int _goldValue;
};

