#pragma once
#include "SceneBase.h"
class SceneManager 
{
private:
    SceneBase* now_scene;

public:
    SceneManager();
    ~SceneManager();

    bool SceneManagement();


};

