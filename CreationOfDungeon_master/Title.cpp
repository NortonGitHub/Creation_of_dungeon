#include "Title.h"



Title::Title() : class_name("title")
{
}


Title::~Title()
{
}

SceneBase * Title::Update()
{

    //nowUI->Update();

    mouse_status = MouseManager::GetMouseStatus(mouse_status);

    return this;
}

void Title::Draw()
{
}
