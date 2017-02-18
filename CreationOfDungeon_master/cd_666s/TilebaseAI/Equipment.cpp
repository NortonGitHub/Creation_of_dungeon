#include "Equipment.h"
#include "../Resources/ResourceManager.h"

//const Equipment::_empty = Equipment(BattleParameter(0, 0, 0, 0), 0);

Equipment::Equipment(BattleParameter bonus, int goldValue, std::string fileName)
    : TreasureContents(goldValue, fileName)
    , _bonusParameter(bonus)
{
}


Equipment::~Equipment()
{
}
