#pragma once
#include "CharaManagerBase.h"
#include "ObstacleBase.h"

class ObstacleManager :
	public CharaManagerBase
{
public:
	ObstacleManager();
	ObstacleManager(std::string stage_num);
	~ObstacleManager();

	void Update();
	void Draw();

	std::string GetManagerName() const { return _name; }

private:
	std::vector<ObstacleBase*> obstacles;
	std::string _name;
};

