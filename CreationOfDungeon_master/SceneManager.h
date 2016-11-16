#pragma once
#include "SceneBase.h"
class SceneManager 
{
private:
	SceneBase* now_scene;

	//UIBase* ui;

public:
	SceneManager();
	~SceneManager();

	void SceneManagement();


};

