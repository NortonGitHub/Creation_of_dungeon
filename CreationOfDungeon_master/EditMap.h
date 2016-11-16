#pragma once
#include "SceneBase.h"
class EditMap :
	public SceneBase
{
public:
	EditMap();
	~EditMap();

	SceneBase* Update();
	void Draw();
};

