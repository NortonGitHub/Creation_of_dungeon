#include "Result.h"



Result::Result()
{
    class_name = "result";
}


Result::~Result()
{
}

SceneBase * Result::Update()
{
    return nullptr;
}

SceneBase * Result::Update(UIManager _ui)
{
//    _ui.Update();
    return this;
}

void Result::Draw()
{
}
