#pragma once

#include "TiledObject.h"
#include <string>

class Bridge : public TiledObject
{
public:
	Bridge(std::string typeName, TiledVector tilePos);
	virtual ~Bridge();

	bool IsOverwritable(TiledObject* overwriter) override;

	virtual void Init() override;
	void Update() override;
	void Draw() override;

private:
	
	std::string typeName;


	std::string GetNameFromTypeName();

};
