#include "Trap.h"



Trap::Trap(TiledVector startPos, int duravity, int cost, int level)
    : TiledObject(startPos)
    , _maxDuravity(duravity)
    , _duravity(duravity)
    , _cost(cost)
    , _level(level)
{
    _type = TiledObject::Type::TRAP;
    _position = startPos.GetWorldPos();
}


Trap::~Trap()
{
}


void Trap::Update()
{
    _duravity++;
    _duravity = min(_maxDuravity, max(_duravity, 0));
}