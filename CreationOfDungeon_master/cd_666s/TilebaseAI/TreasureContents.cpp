#include "TreasureContents.h"
#include "../Resources/ResourceManager.h"


TreasureContents::TreasureContents(std::string ItemName, int goldValue, std::string imageFileName)
    : _goldValue(goldValue)
{
	this->ItemName = ItemName;
    auto path = "resource/graph/item/";
	filePath = path + imageFileName;
    _image = IMAGE_RESOURCE_TABLE->Create(path + imageFileName);
}


TreasureContents::~TreasureContents()
{
}
