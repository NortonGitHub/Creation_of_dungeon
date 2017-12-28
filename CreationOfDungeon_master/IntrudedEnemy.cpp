#include "IntrudedEnemy.h"
#include "cd_666s\TilebaseAI\ColleagueNotifyer.h"
#include "cd_666s\TilebaseAI\TiledObjectMnager.h"




IntrudedEnemy::IntrudedEnemy(BattleParameter params, ColleagueNotifyer & notifyer, std::string enemyName)
	: Character({ 0,0 }, params, notifyer, enemyName, TiledObject::Type::ENEMY)
{
}


IntrudedEnemy::~IntrudedEnemy()
{
}

void IntrudedEnemy::Update()
{
}
