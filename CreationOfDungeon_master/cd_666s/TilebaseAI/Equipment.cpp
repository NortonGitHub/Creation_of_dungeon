#include "Equipment.h"
#include "../Resources/ResourceManager.h"

//const Equipment::_empty = Equipment(BattleParameter(0, 0, 0, 0), 0);

Equipment::Equipment(std::string fileName, BattleParameter bonus, int goldValue)
    : _goldValue(goldValue)
    , _bonusParameter(bonus)
{
    auto path = "resourse/graph/item/";
    _image = IMAGE_RESOURCE_TABLE->Create(path + fileName);
}


Equipment::~Equipment()
{
}
