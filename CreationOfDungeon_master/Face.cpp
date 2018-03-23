#include "Face.h"

Face::Face(Vector2D startPos, BattleParameter param, ColleagueNotifyer & notifyer, std::string name, bool _isBoss)
	: BossBattleObject(startPos, param, notifyer, name, _isBoss)
{
}

Face::~Face()
{
}

void Face::Update()
{
}

void Face::Draw()
{
}

void Face::Init()
{
}
