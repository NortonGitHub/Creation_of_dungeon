#include "SceneBase.h"


SceneBase::SceneBase()
    : _before_pos(0, 0)//, test(Graph("resource/test_666/omote.png"))
{
 //   test.SetPosition(Vector2D(64, 64));
}


SceneBase::~SceneBase()
{

}

void SceneBase::Init(std::string _class_name)
{
    ui_manager = UIManager(_class_name);
}

SceneBase * SceneBase::MainUpdate()
{    //some  process

    //SetUIInstance(ui);

    //ui_manager.Update();

    SceneBase* next_scene = Update(ui_manager);
    
    return next_scene;
}

void SceneBase::MainDraw()
{

    Draw();
    ui_manager.Draw();


    //test.Draw();

}

