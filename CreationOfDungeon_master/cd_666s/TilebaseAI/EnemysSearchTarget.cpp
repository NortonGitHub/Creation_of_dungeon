#include "Enemy.h"
#include "EnemysItem.h"
#include "Monster.h"
#include "EnemysSearch.h"
#include "ColleagueNotifyer.h"

SearchPriorityNode CreateSearcingRuleNode(int priority, SearchPriorityNode::SearchingRange range)
{
    SearchPriorityNode node;
    node._priority = 1;
    node._rangeType = SearchPriorityNode::SearchingRange::Sight;
    return std::move(node);
}


TiledObject* Enemy::SearhTargetByRuleList()
{
    std::vector<TiledObject*> targets;
    auto tilePos = GetTilePos();

    if (_searchRuleList.size() == 0)
    {
        targets.push_back(&_baseTarget);
        return &_baseTarget;
    }

    int bfPriority = _searchRuleList[0]._priority;
    for (auto& rule : _searchRuleList)
    {
        bfPriority = rule._priority;

        //priorityÇ™êÿÇËë÷ÇÌÇ¡ÇΩÇÁîªíËÇ÷
        if (    bfPriority != rule._priority
            &&  0 < targets.size())
        {
            return GetPrimaryTarget<TiledObject>(targets, tilePos);
        }

        //íTçıÇÕÇ±Ç±Ç≈çsÇ§
        rule._searchFunc(targets, tilePos, rule._rangeType);
    }

    //íTÇ∑Ç◊Ç´Ç‡ÇÃÇ™âΩÇ‡Ç»ÇØÇÍÇŒÉSÅ[ÉãÇ÷
    if (targets.size() == 0)
    {
        targets.push_back(&_baseTarget);
        return &_baseTarget;
    }
    else
    {
        return GetPrimaryTarget<TiledObject>(targets, tilePos);
    }
}


void Enemy::BuildSearchingRuleList()
{
    if (GetName() == "healer")
    {
        {
            SearchPriorityNode node;
            node._priority = 2;
            node._rangeType = SearchPriorityNode::SearchingRange::Sight;
            node._searchFunc = std::move([&](std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& type) { SearchItem(targets, tilePos, type); });
            _searchRuleList.push_back(std::move(node));
        }

        {
            SearchPriorityNode node2;
            node2._priority = 3;
            node2._rangeType = SearchPriorityNode::SearchingRange::Field;
            node2._searchFunc = std::move([&](std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& type) { SearchColleague(targets, tilePos, type); });
            _searchRuleList.push_back(std::move(node2));
        }

        std::sort(_searchRuleList.begin(), _searchRuleList.end(),
            [&](const SearchPriorityNode& lhs, const SearchPriorityNode& rhs)
        {
            return (lhs._priority > rhs._priority);
        });

        return;
    }

    if (GetName() == "thief")
    {
        {
            SearchPriorityNode node;
            node._priority = 2;
            node._rangeType = SearchPriorityNode::SearchingRange::Field;
            node._searchFunc = std::move([&](std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& type) { SearchItem(targets, tilePos, type); });
            _searchRuleList.push_back(std::move(node));
        }

        {
            SearchPriorityNode node2;
            node2._priority = 2;
            node2._rangeType = SearchPriorityNode::SearchingRange::Sight;
            node2._searchFunc = std::move([&](std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& type) { SearchMonster(targets, tilePos, type); });
            _searchRuleList.push_back(std::move(node2));
        }

        std::sort(_searchRuleList.begin(), _searchRuleList.end(),
            [&](const SearchPriorityNode& lhs, const SearchPriorityNode& rhs)
        {
            return (lhs._priority > rhs._priority);
        });

        return;
    }

    {
        SearchPriorityNode node;
        node._priority = 2;
        node._rangeType = SearchPriorityNode::SearchingRange::Sight;
        node._searchFunc = std::move([&](std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& type) { SearchItem(targets, tilePos, type); });
        _searchRuleList.push_back(std::move(node));
    }

    {
        SearchPriorityNode node2;
        node2._priority = 2;
        node2._rangeType = SearchPriorityNode::SearchingRange::Sight;
        node2._searchFunc = std::move([&](std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& type) { SearchMonster(targets, tilePos, type); });
        _searchRuleList.push_back(std::move(node2));
    }

    std::sort(_searchRuleList.begin(), _searchRuleList.end(),
        [&](const SearchPriorityNode& lhs, const SearchPriorityNode& rhs)
    {
        return (lhs._priority > rhs._priority);
    });
}


void Enemy::SearchMonster(std::vector<TiledObject*>& targets, const TiledVector& tilePos, SearchPriorityNode::SearchingRange rangeType)
{
    auto target = (rangeType == SearchPriorityNode::SearchingRange::Sight)
        ? SearchTargetInSight<Monster>(tilePos, _sight, true)
        : SearchTargetInField<Monster>(tilePos, true);

    if (target != nullptr)
        targets.push_back(target);
}


void Enemy::SearchItem(std::vector<TiledObject*>& targets, const TiledVector& tilePos, SearchPriorityNode::SearchingRange rangeType)
{
    std::vector<TiledObject*> temp;

    {
        SearchExpression<EnemysItem<Equipment>>::Expressions expressions;
        expressions.push_back([&](const EnemysItem<Equipment>* target, const TiledVector& pos)
        {
            if (target->IsEmpty())
                return false;

            if (_equipItem != nullptr)
                return false;

            //ï ÇÃíáä‘Ç™Ç∑Ç≈Ç…ëŒè€Ç…ÇµÇƒÇ¢ÇÈÇ»ÇÁñ≥éã
            if (!_notifyer.IsChasable(*target))
                return false;

            return true;
        });

        auto target = (rangeType == SearchPriorityNode::SearchingRange::Sight)
            ? SearchTargetInSight<EnemysItem<Equipment>>(tilePos, _sight, expressions, true)
            : SearchTargetInField<EnemysItem<Equipment>>(tilePos, expressions, true);
        if (target != nullptr)
            temp.push_back(target);
    }

    {
        SearchExpression<EnemysItem<ConsumableItem>>::Expressions expressions;
        expressions.push_back([&](const EnemysItem<ConsumableItem>* target, const TiledVector& pos)
        {
            if (target->IsEmpty())
                return false;

            //ï ÇÃíáä‘Ç™Ç∑Ç≈Ç…ëŒè€Ç…ÇµÇƒÇ¢ÇÈÇ»ÇÁñ≥éã
            if (!_notifyer.IsChasable(*target))
                return false;

            //éËéùÇøÇ…ãÛÇ´Ç™Ç†ÇÍÇŒéÊÇËÇ…çsÇ≠
            for (size_t i = 0; i<_consumableItems.size(); ++i)
            {
                if (_consumableItems[i] == nullptr)
                    return true;
            }

            return false;
        });

        auto target = (rangeType == SearchPriorityNode::SearchingRange::Sight)
            ? SearchTargetInSight<EnemysItem<ConsumableItem>>(tilePos, _sight, expressions, true)
            : SearchTargetInField<EnemysItem<ConsumableItem>>(tilePos, expressions, true);

        if (target != nullptr)
            temp.push_back(target);
    }

    targets.push_back(GetPrimaryTarget<TiledObject>(temp, tilePos));
}


void Enemy::SearchColleague(std::vector<TiledObject*>& targets, const TiledVector& tilePos, SearchPriorityNode::SearchingRange rangeType)
{
    SearchExpression<Enemy>::Expressions expressions;
    expressions.push_back([&](const Enemy* target, const TiledVector& pos)
    {
        //î≠å©ëŒè€Ç™é©ï™Ç»ÇÁñ≥éã
        if (target == this)
            return false;

        return true;
    });

    auto target = (rangeType == SearchPriorityNode::SearchingRange::Sight)
        ? SearchTargetInSight<Enemy>(tilePos, _sight, expressions, true)
        : SearchTargetInField<Enemy>(tilePos, expressions, true);

    if (target != nullptr)
        targets.push_back(target);
}