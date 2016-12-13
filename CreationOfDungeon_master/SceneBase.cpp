#include "SceneBase.h"


SceneBase::SceneBase()
    : _before_pos(0, 0)
{
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

    ui_manager.Update();

    SceneBase* next_scene = Update();

    return next_scene;
}

