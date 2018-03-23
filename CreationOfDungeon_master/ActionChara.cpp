#include "ActionChara.h"

ActionChara::ActionChara(Vector2D startPos, BattleParameter param, ColleagueNotifyer & notifyer, std::string name, bool _isBoss)
	: BossBattleObject(startPos, param, notifyer, name, _isBoss)
{
}

ActionChara::~ActionChara()
{
}

void ActionChara::Update()
{
}

void ActionChara::Draw()
{
}

void ActionChara::Init()
{
}
