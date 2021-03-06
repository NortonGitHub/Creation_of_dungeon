#include "Title.h"
#include "FunctionTransScene.h"
#include "cd_666s/Resources/ResourceManager.h"
#include "ShopAssortment.h"
#include "MoneyManager.h"

Title::Title() 
    : class_name("title")
    , title("resource/title.png")
    , _bgm("resource/sound/Area1.ogg")
    , _se("resource/sound/decide.wav")
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

    std::string _ui_name;

    _ui.Update(_functions,_ui_name);

    for (auto f : _functions) {
        if (f.find("_B") != std::string::npos) {
            _se.Play();
            return FunctionTransScene::GetSceneBase("edit");
        }
        else if (f.find("MOVE") != std::string::npos) {
            _se.Play();
			ShopAssortment::getInstance()->setShopItemList();
			MoneyManager::getInstance()->InitMoney();
            return FunctionTransScene::GetSceneBase("world_map");
        }
        else if (f.find("QUIT") != std::string::npos) {
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
