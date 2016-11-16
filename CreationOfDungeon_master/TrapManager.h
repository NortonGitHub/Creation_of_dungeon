#pragma once
#include "CharaManagerBase.h"
#include "TrapBase.h"


class TrapManager : public TrapBase{
public:
	TrapManager();
	TrapManager(std::string stage_num);
	~TrapManager();

	void Update();
	void Draw();

	std::string GetManagerName() const { return _name; }

private:
	std::vector<TrapBase*> traps;
	std::string _name;
};