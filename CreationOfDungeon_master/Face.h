#pragma once
#include "BossBattleObject.h"

class GraphArray;

class Face : public BossBattleObject
{
public:
	Face(Vector2D startPos, BattleParameter param, ColleagueNotifyer & notifyer, std::string name, bool _isBoss);
	~Face();

	void Update() override;
	void Draw() override;

	void Init() override;

	//bool IsBrakeable(int brokerLevel) const { return _level <= brokerLevel; };

	//能動動作できるオブジェクトから呼び出される関数
	void Interact(Character& character) override {};

protected:

};


