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

    //�T���̗D��x
    int _priority;

    //�T���͈�
    SearchingRange _rangeType;

    std::function<void(std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchingRange& type)> _searchFunc;
};
