#include "Game.h"
#include "MouseManager.h"
#include "FunctionSyncParameter.h"
#include "cd_666s/InputManager/InputManager.h"
#include "cd_666s/DebugDraw.h"
#include "cd_666s/Resources/ResourceManager.h"
#include "Main.h"
#include "Title.h"

Game::Game()
    :_stageNumber(1)
    , _fadeoutCount(0)
    , _state(GameState::READY)
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
    RESOURCE_TABLE->Refresh();
}

SceneBase * Game::Update(UIManager _ui)
{
    bool goTitle = false;
    switch (_state)
    {
    case Game::GameState::READY:
        GameReadyUpdate();
        break;

    case Game::GameState::GAMING:
        GamingUpdate();
        break;

    case Game::GameState::GAME_OVER:
        goTitle = GameOverUpdate();
        break;

    case Game::GameState::WAVE_CLEAR:
        StageClearUpdate();
        break;

    case Game::GameState::GAME_CLEAR:
        goTitle = GameClearUpdate();
        break;
    default:
        break;
    }

    if (goTitle)
    {
        return new Title();
    }

    return this;
}

void Game::Draw()
{
    switch (_state)
    {
    case Game::GameState::READY:
        GameReadyDraw();
        break;

    case Game::GameState::GAMING:
        GamingDraw();
        break;

    case Game::GameState::GAME_OVER:
        GameOverDraw();
        break;

    case Game::GameState::WAVE_CLEAR:
        StageClearDraw();
        break;

    case Game::GameState::GAME_CLEAR:
        GameClearDraw();
        break;
    default:
        break;
    }
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

    _state = GameState::READY;
    _fadeoutCount = 0;


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


bool Game::GameOverUpdate() {

    _fadeoutCount++;

    if (_fadeoutCount > 200
        && MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) 
    {
        return true;
    }

    return false;
}


void Game::GameOverDraw()
{
    double blend = double(_fadeoutCount) * 17 / 10;

    if (blend > 150) {
        blend = 150;
    }

    auto color = Color4(0, 0, 0, 1.0 * blend / 255);
    Debug::DrawRectWithSize(Vector2D(0, 0), Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT), color, true);

    if (_fadeoutCount > 150) {
        Debug::DrawString(Vector2D(200, 200), "ガメオベラ", ColorPalette::RED4);
    }
    if (_fadeoutCount > 200) {
        Debug::DrawString(Vector2D(200, 400), "左クリックで戻る", ColorPalette::WHITE4);
    }
}


bool Game::StageClearUpdate() {

    _fadeoutCount++;
    if (_fadeoutCount > 200 && MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) 
    {
        Clear();
        Init();
        return true;
    }

    return false;
}

void Game::StageClearDraw() {

    double blend = double(_fadeoutCount) * 17 / 10;

    if (blend > 150) {
        blend = 150;
    }

    auto color = Color4(0, 0, 0, 1.0 * blend / 255);
    Debug::DrawRectWithSize(Vector2D(0, 0), Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT), color, true);

    if (_fadeoutCount > 150) {
        Debug::DrawString(Vector2D(200, 200), "ステージクリア", ColorPalette::RED4);
    }
    if (_fadeoutCount > 200) {
        Debug::DrawString(Vector2D(200, 400), "左クリックで次へ進む", ColorPalette::WHITE4);
    }

}

bool Game::GameClearUpdate() {

    _fadeoutCount++;

    if (_fadeoutCount > 200 && MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) 
    {
        return true;
    }

    return false;

}

void Game::GameClearDraw() {

    double blend = double(_fadeoutCount) * 17 / 10;

    if (blend > 150) {
        blend = 150;
    }

    auto color = Color4(0, 0, 0, 1.0 * blend / 255);
    Debug::DrawRectWithSize(Vector2D(0, 0), Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT), color, true);

    if (_fadeoutCount > 150) {
        Debug::DrawString(Vector2D(200, 200), "ゲームクリア", ColorPalette::RED4);
    }
    if (_fadeoutCount > 200) {
        Debug::DrawString(Vector2D(200, 400), "左クリックで戻る", ColorPalette::WHITE4);
    }
}

bool Game::GameReadyUpdate()
{
    if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) 
    {
        _state = GameState::GAMING;
        return true;
    }

    return false;

}

void Game::GameReadyDraw(){

    auto color = Color4(0, 0, 0, 0.7);
    Debug::DrawRectWithSize(Vector2D(0, 0), Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT), color, true);
    Debug::DrawString(Vector2D(200, 200), "左クリックで開始", ColorPalette::RED4);
}

void Game::GamingUpdate()
{
    if (_dungeon->HasClear())
    {
        if (_stageNumber < 3)
        {
            _stageNumber++;
            _state = GameState::WAVE_CLEAR;
            return;
        }
        else
        {
            _state = GameState::GAME_CLEAR;
            return;
        }
    }

    if (_dungeon->HasGameOver())
    {
        _state = GameState::GAME_OVER;
    }

    _dungeon->Update();
}

void Game::GamingDraw()
{
    _dungeon->Draw();
}