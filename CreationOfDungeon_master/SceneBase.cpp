#include "SceneBase.h"


SceneBase::SceneBase()
	: _before_pos(0, 0)
{
	ui_manager = UIManager(GetClassName());
}


SceneBase::~SceneBase()
{
}

SceneBase * SceneBase::MainUpdate()
{    //some  process

	//SetUIInstance(ui);

	ui_manager.Update();

	SceneBase* next_scene = Update();

	return next_scene;
}

