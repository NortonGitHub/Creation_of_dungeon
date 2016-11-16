#pragma once
#include "SceneBase.h"
class GameOver :
	public SceneBase
{
public:
	GameOver();
	~GameOver();

	SceneBase* Update();
	void Draw();
};

