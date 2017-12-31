#pragma once
#include <memory>
#include "TreasureContents.h"
#include "BattleParameter.h"
#include "../Resources/ImageResource.h"

class Equipment : public TreasureContents
{
public:

    Equipment(std::string ItemName, BattleParameter bonusParam, int goldValue, std::string imageFileName);
    ~Equipment();

    BattleParameter GetBonusParam() const { return _bonusParameter; }

    //const static Equipment _empty;

private:

    BattleParameter _bonusParameter;

};
