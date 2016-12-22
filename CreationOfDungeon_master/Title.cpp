#include "Title.h"



Title::Title() : class_name("title"), test("resourse/test_666/omote")
{
    test.SetPosition(Vector2D(0, 128));
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

SceneBase * Title::Update(UIManager _ui)
{
    mouse_status = MouseManager::GetMouseStatus(mouse_status);

    _ui.Update();

    return this;
}

void Title::Draw()
{
//    test.Draw();
}
