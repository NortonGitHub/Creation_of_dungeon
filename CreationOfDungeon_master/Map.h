#pragma once
#include "SceneBase.h"
class Map :
	public SceneBase
{
public:
	Map();
	~Map();

	SceneBase* Update();
	void Draw();
};

