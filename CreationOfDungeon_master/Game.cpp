#include "Game.h"
#include "MouseManager.h"
#include "FunctionSyncParameter.h"

Game::Game()
    :stage_num("1-1"),
    mouse_status(MouseContent()), test("resourse/test_666/scene_g")
{
    class_name = "game";

    chara_manager = CharaManager(stage_num);

    _functions.reserve(20);
}


Game::~Game()
{
    _functions.clear();
}

SceneBase * Game::Update(UIManager _ui)
{

    _ui.Update(_functions);


    mouse_status = MouseManager::GetMouseStatus(mouse_status);

    chara_manager.Update(mouse_status);

    map_process_manager.Update(mouse_status);
    
    for(auto f : _functions){
        if(f == "CHANGE"){
            FunctionSyncParameter::SyncParamater();
        }
    }
    return this;
}

void Game::Draw()
{
    chara_manager.Draw();

    map_process_manager.Draw();

//    test.Draw();
}
