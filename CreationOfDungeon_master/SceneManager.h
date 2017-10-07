#pragma once
#include "SceneBase.h"
class SceneManager 
{
private:
    SceneBase* now_scene;

	Graph test;

public:
    SceneManager();
    ~SceneManager();

    bool SceneManagement();


};

