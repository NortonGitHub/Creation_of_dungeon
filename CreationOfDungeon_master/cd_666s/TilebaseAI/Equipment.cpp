#include "Equipment.h"
#include "../Resources/ResourceManager.h"

//const Equipment::_empty = Equipment(BattleParameter(0, 0, 0, 0), 0);

Equipment::Equipment(BattleParameter bonus, int goldValue)
    : _goldValue(goldValue)
    , _bonusParameter(bonus)
{
    _image = IMAGE_RESOURCE_TABLE->Create("resourse/graph/item/book.png");
}


Equipment::~Equipment()
{
}
