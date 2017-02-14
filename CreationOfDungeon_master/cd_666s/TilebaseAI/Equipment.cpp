#include "Equipment.h"

//const Equipment::_empty = Equipment(BattleParameter(0, 0, 0, 0), 0);

Equipment::Equipment(BattleParameter bonus, int goldValue)
    : _goldValue(goldValue)
    , _bonusParameter(bonus)
{
}


Equipment::~Equipment()
{
}
