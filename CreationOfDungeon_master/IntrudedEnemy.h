#pragma once
#include "cd_666s\TilebaseAI\Character.h"
#include "cd_666s\TilebaseAI\Equipment.h"
#include "cd_666s\TilebaseAI\ColleagueNotifyer.h"
#include "cd_666s\TilebaseAI\ConsumableItem.h"
#include <memory>
#include <string>

class ColleagueNotifyer;

class IntrudedEnemy :
	public Character
{
public:
	IntrudedEnemy(BattleParameter params, ColleagueNotifyer& notifyer, std::string enemyName);
	~IntrudedEnemy();

	void Update() override;

	static bool HasWipeOuted()
	{
		return false;
	}

private:
};

