#include "Trap.h"



Trap::Trap(TiledVector startPos, int duravity, int level)
    : TiledObject(startPos)
    , _duravity(duravity)
    , _cost(duravity)
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
    _duravity = min(_cost, max(_duravity, 0));

	if (IsActivatable())
		Activate();
}

//トラップを起動できるかどうか
bool Trap::IsActivatable() const
{
	return IsEnable();
}

//トラップを起動
void Trap::Activate()
{
	_duravity -= _cost;
}