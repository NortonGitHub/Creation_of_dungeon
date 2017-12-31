#pragma once
#include <memory>
#include "TreasureContents.h"
#include "../Resources/ImageResource.h"

class ConsumableItem : public TreasureContents
{
public:
    ConsumableItem(std::string ItemName,int goldValue, std::string imageFileName);
    ~ConsumableItem();

private:

};

