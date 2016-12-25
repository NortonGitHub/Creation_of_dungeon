#pragma once
#include "SceneBase.h"
class SceneManager 
{
private:
    SceneBase* now_scene;

    //UIBase* ui;

    Graph test;

public:
    SceneManager();
    ~SceneManager();

    bool SceneManagement();


};

