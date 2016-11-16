#pragma once
#include "SceneBase.h"
class Title :
	public SceneBase
{
public:
	Title();
	~Title();

	SceneBase* Update();
	void Draw();

};

