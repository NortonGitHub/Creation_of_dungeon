#pragma once
#include <memory>
#include "../Resources/ImageResource.h"

class TreasureContents
{
public:
    TreasureContents(int goldValue, std::string imageFileName);
    ~TreasureContents();

    int GetGoldValue() const { return _goldValue; };

    std::shared_ptr<ImageResource> _image;

private:
    int _goldValue;
};

