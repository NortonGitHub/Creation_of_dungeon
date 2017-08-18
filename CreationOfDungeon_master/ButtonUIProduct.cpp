#include "ButtonUIProduct.h"
#include "DxLib.h"
#include "MouseManager.h"

#include "FunctionTransScene.h"



ButtonUIProduct::ButtonUIProduct(UIContent ui_contents) : ui(ui_contents)
{
    is_click = false;

    //ui.SetFunction(GetUI(ui.GetDataName()));

    test_handle = LoadGraph("test_666/ura.png");
}


ButtonUIProduct::~ButtonUIProduct()
{
}

std::string ButtonUIProduct::Update()
{

    Vector2D mcv = MouseManager::GetMousePos();

    std::string func_data = "";
    if (MouseManager::IsClicked("left", is_click) && MouseManager::OnMouseOver(mcv,ui.GetPosition(),ui.GetSizePos())) {
        //ui.GetFunction();
        /*àÍâûâûã}èàíu*/
        /*
        if (ui.GetDataName().find("hello") != std::string::npos) {
            func_data = "game";
        }
        else if (ui.GetDataName().find("start") != std::string::npos) {
           /// return std::bind(&ButtonUIProduct::MoveSceneFunction, this);
        }
        else if (ui.GetDataName().find("quit") != std::string::npos) {
            //return std::bind(&ButtonUIProduct::QuitFunction, this);
            auto n = 0;
        }
        */
        /*
        if (ui.GetFunctionType().find("MOVE") != std::string::npos){
            func_data = "MOVE";
        }else if(ui.GetFunctionType().find("QUIT")  != std::string::npos){
            func_data = "QUIT";
        }
        */
        
        func_data = ui.GetFunctionType();
    }
    
    return func_data;
}

void ButtonUIProduct::Draw()
{
    ui.Draw();
}

void ButtonUIProduct::MoveSceneFunction(std::string button_name)
{
   /* 

    if (button_name.find("game") != std::string::npos) {
        return new Game();
    }
    return nullptr;
    */
}

void ButtonUIProduct::QuitFunction()
{
    //return nullptr;
}
