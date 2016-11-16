#pragma once
#include "SceneBase.h"
class GameClear :
	public SceneBase
{
public:
	GameClear();
	~GameClear();

	SceneBase* Update();
	void Draw();
};

