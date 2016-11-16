#include "MonsterManager.h"



MonsterManager::MonsterManager()
{
	monsters.reserve(10);
}

MonsterManager::MonsterManager(std::string stage_num)
	: _name("monster")
{
}


MonsterManager::~MonsterManager()
{
	std::vector<MonsterBase*>().swap(monsters);
}

void MonsterManager::Update()
{
}

void MonsterManager::Draw()
{
}
