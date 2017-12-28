#pragma once
#include <queue>
#include "cd_666s\TilebaseAI\Character.h"

class BossBattle
{
public:
	BossBattle();
	~BossBattle();

	void Init(std::string stageNum);

	void Update();

	void SetBattleObject(std::vector<std::shared_ptr<TiledObject>>& objects, std::shared_ptr<TiledObject> intruder);

	bool WasBossKilled() const { return _wasBossKilled; }


private:
	struct Party {
		bool _isLead;
		BattleParameter _param;
	};

	enum class BattleSequence{
		None,
		Starting,
		EnemyAttack,
		BossAttack,
		BossDied,
	};

	bool HasKilled(BattleParameter atk, BattleParameter& dff);

	void GenerateObject(std::string typeName);

	void Starting();
	void EnemyAttack();
	void BossAttack();
	void BossDied();

	BattleSequence now_situation;

	std::queue<Party> _intruders;	//êÌÇ¢Ç…éQâ¡ÇµÇƒÇ¢ÇÈñ`åØé“ÇΩÇø
	BattleParameter _boss;

	int _sequenceTimer;

	bool _wasBossKilled;
};

