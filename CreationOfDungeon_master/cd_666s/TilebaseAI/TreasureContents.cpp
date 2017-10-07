#include "TreasureContents.h"
#include "../Resources/ResourceManager.h"


TreasureContents::TreasureContents(int goldValue, std::string imageFileName)
    : _goldValue(goldValue)
{
    auto path = "resource/graph/item/";
    _image = IMAGE_RESOURCE_TABLE->Create(path + imageFileName);
}


TreasureContents::~TreasureContents()
{
}
