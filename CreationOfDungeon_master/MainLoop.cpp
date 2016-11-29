#include "MainLoop.h"
#include "SceneManager.h"
#include "DxLib.h"

MainLoop::MainLoop()
{
}


MainLoop::~MainLoop()
{
}

void MainLoop::GameLoop()
{

    SetDrawScreen(DX_SCREEN_BACK);

    SceneManager scene_manager;
    while (ProcessMessage() == 0) {
        scene_manager.SceneManagement();

        ClearDrawScreen();

        ScreenFlip();
    }
}
