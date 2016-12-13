#include "MainLoop.h"
#include "SceneManager.h"
#include "DxLib.h"

MainLoop::MainLoop() : scene_manager(SceneManager())
{
}


MainLoop::~MainLoop()
{
}

void MainLoop::GameLoop()
{

    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0) {

        ClearDrawScreen();

        scene_manager.SceneManagement();

        ScreenFlip();
    }
}
