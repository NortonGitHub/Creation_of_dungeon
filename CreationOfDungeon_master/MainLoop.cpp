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
    Graph graph1("resourse/test_666/omote");

    Graph graph2("resourse/test_666/ura");

    graph1.SetPosition(Vector2D(64,0));

    while (ProcessMessage() == 0) {

        ClearDrawScreen();

        //graph1.Draw();

        /*
        if(!scene_manager.SceneManagement()){
            break;
        }
        */

        //graph2.Draw();

        ScreenFlip();
    }
}
