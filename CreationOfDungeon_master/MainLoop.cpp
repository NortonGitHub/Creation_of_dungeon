#include "MainLoop.h"
#include "SceneManager.h"
#include "DxLib.h"


MainLoop::MainLoop() //: scene_manager(SceneManager())
{
}


MainLoop::~MainLoop()
{
}

void MainLoop::GameLoop()
{
    Graph graph("resourse/test_666/tofu");

    auto size = graph.GetSize();
    Graph graph_extended("resourse/test_666/tofu", size, Vector2D(2, 2));


    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0) {

        ClearDrawScreen();

        //scene_manager.SceneManagement();
        graph.Draw();
        graph_extended.Draw();

        ScreenFlip();
    }
}
