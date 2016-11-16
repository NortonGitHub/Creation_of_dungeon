#pragma once
#include "SceneBase.h"
#include "MapProcessManager.h"
#include "CharaManager.h"

class Game :
	public SceneBase
{
public:
	Game();
	~Game();

	SceneBase* Update();
	void Draw();

private:

	std::string stage_num;

	CharaManager chara_manager;

	MapProcessManager map_process_manager;

	MouseContent mouse_status;

};

