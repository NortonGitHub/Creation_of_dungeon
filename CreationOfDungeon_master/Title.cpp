#include "Title.h"

#include "FunctionTransScene.h"

Title::Title() : class_name("title"), test("resourse/test_666/omote")
{
    _functions.reserve(20);
    test.SetPosition(Vector2D(0, 128));
}


Title::~Title()
{
    _functions.clear();
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

    _functions.resize(0);

    _ui.Update(_functions);

    for (auto f : _functions) {
        if(f.find("MOVE") != std::string::npos){
            return FunctionTransScene::GetSceneBase("game");
        } else if(f.find("FUNC") != std::string::npos){
            return nullptr;
        }
    }


    return this;
}

void Title::Draw()
{
    //    test.Draw();
}

SceneBase * Title::UpdateFunctions()
{
    return nullptr;
}
