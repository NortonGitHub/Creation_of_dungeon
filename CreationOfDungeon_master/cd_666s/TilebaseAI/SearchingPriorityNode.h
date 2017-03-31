#pragma once
#include "EnemysSearch.h"
#include "TiledObject.h"

struct SearchPriorityNode
{
    enum class SearchingRange
    {
        Sight,
        Field
    };

    //’Tõ‚Ì—Dæ“x
    int _priority;

    //’Tõ”ÍˆÍ
    SearchingRange _rangeType;

    std::function<void(std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchingRange& type)> _searchFunc;
};
