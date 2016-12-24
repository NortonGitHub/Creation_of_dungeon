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
    Graph graph1("resourse/test_666/omote");

    Graph graph2("resourse/test_666/ura");

    graph1.SetPosition(Vector2D(64,0));

    while (ProcessMessage() == 0) {

        ClearDrawScreen();

        //graph1.Draw();

        if(!scene_manager.SceneManagement()){
            break;
        }

        //graph2.Draw();

        ScreenFlip();
    }
}
