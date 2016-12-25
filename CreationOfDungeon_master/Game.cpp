#include "Game.h"
#include "MouseManager.h"
#include "FunctionSyncParameter.h"
#include "cd_666s/InputManager/KeyInput.h"
#include "cd_666s/InputManager/InputManager.h"

Game::Game()
    :stage_num("1-1"),
    mouse_status(MouseContent()), test("resourse/test_666/scene_g"),
    _stageNumber(1)
{
    class_name = "game";

    chara_manager = CharaManager(stage_num);

    _functions.reserve(20);

    KEYBOARD->AddEvent(KeyInput::KeyType::KEY_LSHIHT
        , ButtonTypeInputEvent::State::Down
        , [&]()
    {
        Clear();
        Init();
    });

    Init();
}


Game::~Game()
{
    _functions.clear();

    if (_dungeon != nullptr)
    {
        delete _dungeon;
        _dungeon = nullptr;
    }
    INPUT_MGR->Clear();
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


    if (_dungeon->HasClear())
    {
        _stageNumber++;

        Clear();
        Init();
        return this;
    }

    if (_dungeon->HasGameOver())
    {
        Clear();
        Init();
        return this;
    }

    _dungeon->Update();
    return this;
}

void Game::Draw()
{
    chara_manager.Draw();

    map_process_manager.Draw();

//    test.Draw();
}


void Game::Init()
{
    if (_dungeon != nullptr)
    {
        delete _dungeon;
        _dungeon = nullptr;
    }

    _dungeon = new Dungeon(std::to_string(_stageNumber));
    _dungeon->Init();
}


void Game::Clear()
{
    _dungeon->Clear();
}