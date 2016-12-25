#pragma once
#include "SceneManager.h"

class MainLoop
{
public:
    MainLoop();
    ~MainLoop();

    void GameLoop();

private:

    SceneManager scene_manager;

    void Init();
    void Terminate();
};

