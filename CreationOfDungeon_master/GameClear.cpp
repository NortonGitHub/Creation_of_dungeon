#include "GameClear.h"



GameClear::GameClear()
{
    class_name = "clear";
}


GameClear::~GameClear()
{
}

SceneBase * GameClear::Update()
{
    return nullptr;
}

SceneBase * GameClear::Update(UIManager _ui)
{
    //_ui.Update();
    return this;
}

void GameClear::Draw()
{
}
