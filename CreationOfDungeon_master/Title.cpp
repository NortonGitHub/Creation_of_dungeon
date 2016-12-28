#include "Title.h"
#include "FunctionTransScene.h"
#include "cd_666s/Resources/ResourceManager.h"

Title::Title() 
    : class_name("title")
    , title("resourse/title")
    , _bgm("sound/Stage_N_Noon.ogg")
    , _se("sound/decide.wav")
{
    _functions.reserve(20);
    title.SetPosition(Vector2D(0, 0));

    _bgm.Play();
    _bgm.SetVolume(200);
}


Title::~Title()
{
    _functions.clear();
    _bgm.Stop();
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
        if (f.find("MOVE") != std::string::npos){
            _se.Play();
            return FunctionTransScene::GetSceneBase("game");
        } else if(f.find("FUNC") != std::string::npos){
            _se.Play();
            return nullptr;
        }
    }

    if (!_bgm.IsPlaying())
        _bgm.Play();


    return this;
}

void Title::Draw()
{
        title.Draw();
}

SceneBase * Title::UpdateFunctions()
{
    return nullptr;
}
