#include "ConsumableItem.h"


ConsumableItem::ConsumableItem(std::string ItemName, int goldValue, std::string imageFileName)
    : TreasureContents(ItemName, goldValue, imageFileName)
{
}


ConsumableItem::~ConsumableItem()
{
}
