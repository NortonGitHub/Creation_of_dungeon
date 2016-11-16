#include "ObstacleManager.h"



ObstacleManager::ObstacleManager()
{
	obstacles.reserve(10);
}

ObstacleManager::ObstacleManager(std::string stage_num)
	: _name("obstacle")
{
}


ObstacleManager::~ObstacleManager()
{
	std::vector<ObstacleBase*>().swap(obstacles);
}

void ObstacleManager::Update()
{
}

void ObstacleManager::Draw()
{
}
