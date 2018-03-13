#include "Equipment.h"
#include "../Resources/ResourceManager.h"

//const Equipment::_empty = Equipment(BattleParameter(0, 0, 0, 0), 0);

Equipment::Equipment(std::string ItemName, BattleParameter bonusParam, int goldValue, std::string imageFileName)
    : TreasureContents(ItemName,goldValue, imageFileName)
    , _bonusParameter(bonusParam)
{
}


Equipment::~Equipment()
{
}
