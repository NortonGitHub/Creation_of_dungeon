#pragma once
#include "BossBattleObject.h"

class GraphArray;

class ActionChara : public BossBattleObject
{
public:
	ActionChara(Vector2D startPos, BattleParameter param, ColleagueNotifyer & notifyer, std::string name, bool _isBoss);
	~ActionChara();

	void Update() override;
	void Draw() override;

	void Init() override;

	//bool IsBrakeable(int brokerLevel) const { return _level <= brokerLevel; };

	//能動動作できるオブジェクトから呼び出される関数
	void Interact(Character& character) override {};

protected:

};


