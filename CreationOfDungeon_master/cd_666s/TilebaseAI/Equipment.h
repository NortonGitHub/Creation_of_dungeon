#pragma once
#include <memory>
#include "BattleParameter.h"
#include "../Resources/ImageResource.h"

class Equipment
{
public:

    Equipment(std::string fileName, BattleParameter bonusParam, int goldValue);
    ~Equipment();

    BattleParameter GetBonusParam() const { return _bonusParameter; }
    int GetGoldValue() const { return _goldValue; };

    //const static Equipment _empty;

    std::shared_ptr<ImageResource> _image;

private:

    BattleParameter _bonusParameter;
    int _goldValue;
};

