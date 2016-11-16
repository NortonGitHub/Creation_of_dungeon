#pragma once
#include "CharaManagerBase.h"
#include "HeroBase.h"

class HeroManager :
	public CharaManagerBase
{
public:
	HeroManager();
	HeroManager(std::string stage_num);
	~HeroManager();

	void Update();
	void Draw();

	std::string GetManagerName() const { return _name; }

private:
	std::vector<CharaBase*> heroes;
	std::string _name;
};

