#pragma once
#include <memory>
#include "../Resources/ImageResource.h"

class TreasureContents
{
public:
	TreasureContents(std::string ItemName, int goldValue, std::string imageFileName);
    ~TreasureContents();

    int GetGoldValue() const { return _goldValue; };
	std::string GetItemName() const { return ItemName; };
	std::string GetfilePath() const { return filePath; };

    std::shared_ptr<ImageResource> _image;

private:
    int _goldValue;

	std::string ItemName;
	std::string filePath;

};

