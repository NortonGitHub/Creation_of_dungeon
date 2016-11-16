#pragma once
#include <vector>
#include <string>
class CharaManagerBase
{
public:
	CharaManagerBase();
	~CharaManagerBase();

	virtual void Update() = 0;
	virtual void Draw();

	virtual std::string GetManagerName() const = 0;
};

