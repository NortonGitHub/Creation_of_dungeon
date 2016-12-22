#include "ButtonUIProduct.h"
#include "DxLib.h"
#include "MouseManager.h"
#include "Game.h"

ButtonUIProduct::ButtonUIProduct(UIContent ui_contents) : ui(ui_contents)
{
    is_click = false;

    //ui.SetFunction(GetUI(ui.GetDataName()));

    test_handle = LoadGraph("resourse/test_666/ura.png");
}


ButtonUIProduct::~ButtonUIProduct()
{
}

void ButtonUIProduct::Update()
{
    if (MouseManager::IsClicked("left", is_click)) {
        //ui.GetFunction();
        /*àÍâûâûã}èàíu*/
        if (ui.GetDataName().find("hello") != std::string::npos) {
            //ñ‚ëËî≠ê∂
        }
        else if (ui.GetDataName().find("start") != std::string::npos) {
           /// return std::bind(&ButtonUIProduct::MoveSceneFunction, this);
        }
        else if (ui.GetDataName().find("quit") != std::string::npos) {
            //return std::bind(&ButtonUIProduct::QuitFunction, this);
            auto n = 0;
        }
    }
}

void ButtonUIProduct::Draw()
{
    ui.Draw();
}

SceneBase* ButtonUIProduct::MoveSceneFunction()
{
    return new Game();
}

void ButtonUIProduct::QuitFunction()
{
    //return nullptr;
}
