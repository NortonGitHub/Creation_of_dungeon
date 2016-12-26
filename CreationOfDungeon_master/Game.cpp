#include "Game.h"
#include "MouseManager.h"
#include "FunctionSyncParameter.h"
#include "cd_666s/InputManager/KeyInput.h"
#include "cd_666s/InputManager/InputManager.h"

Game::Game()
    :_stageNumber(1)
{
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
    if (_dungeon->HasClear())
    {
        if (_stageNumber < 3)
        {
            _stageNumber++;
        }

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
    _dungeon->Draw();
}


void Game::Init()
{
    switch (_stageNumber)
    {
    case 1:
        TILE_SIZE = 48;
        break;
    case 2:
        TILE_SIZE = 40;
        break;
    case 3:
        TILE_SIZE = 32;
        break;
    };

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