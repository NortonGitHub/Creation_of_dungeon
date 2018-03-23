#pragma once
#include <queue>
#include "cd_666s\TilebaseAI\Character.h"
#include "BossBattleObject.h"

class BossBattle
{
public:
	BossBattle();
	~BossBattle();

	void Init(std::string stageNum, std::vector<std::shared_ptr<TiledObject>>& objects, ColleagueNotifyer &notifyer);

	void Update();

//	void SetBattleObject(std::vector<std::shared_ptr<TiledObject>>& objects, std::shared_ptr<TiledObject> intruder);
	void SetBattleObject( std::shared_ptr<TiledObject>& intruder, ColleagueNotifyer& notifyer);

	//ボス部屋にいる侵入者の情報を後ろから取得
	std::shared_ptr<TiledObject> GetIntruderObject() const { return (_intruders.empty() ? nullptr : _intruders.back()); }

	bool WasBossKilled() const { return _wasBossKilled; }


private:
	/*
	struct Party {
		bool _isLead;			//戦闘か否か
		BattleParameter _param; //
	};
	*/

	enum class BattleSequence{
		None,
		Ready,
		EnemyAttack,
		BossAttack,
		BossDied,
	};

	bool HasKilled(BattleParameter& atk, BattleParameter& dff);

	void GenerateObject(std::string typeName);

	void Ready();
	void EnemyAttack();
	void BossAttack();
	void BossDied();

	BattleSequence now_situation;

	std::deque<std::shared_ptr<BossBattleObject>> _intruders;	//戦いに参加している冒険者たち
	std::shared_ptr<BossBattleObject> _boss;
	//BattleParameter _boss;

	int _sequenceTimer;
	const int _readyTime;	//一回の戦闘前シーンフレーム
	const int _battleTime;	//一回の攻撃シーンフレーム
	const int _diedTime;	//ボス死亡演出シーンフレーム

	bool _wasBossKilled;
};

