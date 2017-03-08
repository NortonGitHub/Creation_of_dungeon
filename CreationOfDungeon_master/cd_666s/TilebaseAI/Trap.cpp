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

//�g���b�v���N���ł��邩�ǂ���
bool Trap::IsActivatable() const
{
	return IsEnable();
}

//�g���b�v���N��
void Trap::Activate()
{
	_duravity -= _cost;
}