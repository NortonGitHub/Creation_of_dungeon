#pragma once
#include "Enemy.h"

template <>
void Enemy::SearchTarget<Monster>(std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& rangeType)
{
    auto target = (rangeType == SearchPriorityNode::SearchingRange::Sight)
        ? SearchTargetInSight<Monster>(tilePos, _sight, true)
        : SearchTargetInField<Monster>(tilePos, true);

    if (target != nullptr)
        targets.push_back(target);
}


template <>
void Enemy::SearchTarget<EnemysItem<Equipment>>(std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& rangeType)
{
    SearchExpressions<EnemysItem<Equipment>> expressions;
    expressions.push_back([&](const EnemysItem<Equipment>* target, const TiledVector& pos)
    {
        if (target->IsEmpty())
            return false;

        if (_equipItem != nullptr)
            return false;

        //•Ê‚Ì’‡ŠÔ‚ª‚·‚Å‚É‘ÎÛ‚É‚µ‚Ä‚¢‚é‚È‚ç–³‹
        if (!_notifyer.IsChasable(*target))
            return false;

        return true;
    });

    auto target = (rangeType == SearchPriorityNode::SearchingRange::Sight)
        ? SearchTargetInSight<EnemysItem<Equipment>>(tilePos, _sight, expressions, true)
        : SearchTargetInField<EnemysItem<Equipment>>(tilePos, expressions, true);
    if (target != nullptr)
        targets.push_back(target);
}


template <>
void Enemy::SearchTarget<EnemysItem<ConsumableItem>>(std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& rangeType)
{
    SearchExpressions<EnemysItem<ConsumableItem>> expressions;
    expressions.push_back([&](const EnemysItem<ConsumableItem>* target, const TiledVector& pos)
    {
        if (target->IsEmpty())
            return false;

        //•Ê‚Ì’‡ŠÔ‚ª‚·‚Å‚É‘ÎÛ‚É‚µ‚Ä‚¢‚é‚È‚ç–³‹
        if (!_notifyer.IsChasable(*target))
            return false;

        //è‚¿‚É‹ó‚«‚ª‚ ‚ê‚Îæ‚è‚És‚­
        for (size_t i = 0; i < _consumableItems.size(); ++i)
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
        targets.push_back(target);
}

template <>
void Enemy::SearchTarget<Enemy>(std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& rangeType)
{
    SearchExpressions<Enemy> expressions;
    expressions.push_back([&](const Enemy* target, const TiledVector& pos)
    {
        //”­Œ©‘ÎÛ‚ª©•ª‚È‚ç–³‹
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