#include "Game.h"
#include "MouseManager.h"
#include "FunctionSyncParameter.h"
#include "cd_666s/InputManager/InputManager.h"
#include "cd_666s/DebugDraw.h"
#include "cd_666s/Resources/AllResourceManager.h"
#include "Main.h"
#include "WorldMap.h"

Game::Game(int stageNumber)
    :_stageNumber(stageNumber)
    , _fadeoutCount(0)
    , _fadeinInterval(100)
    , _fadingInterval(200)
    , _fadeoutInterval(255)
    , _fadingout(true)
    , _state(GameState::READY)
    , _bgm("resource/sound/Stage_N_Noon.ogg")
{
    KEYBOARD->AddEvent(KeyInput::KeyType::KEY_LSHIHT
        , ButtonTypeInputEvent::State::Down
        , [&]()
    {
        Clear();
        Init();
    });

    _bgm.SetVolume(220);
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

    case Game::GameState::PAUSE:
        goTitle = PauseUpdate();
        break;

    case Game::GameState::GAME_OVER:
        goTitle = GameOverUpdate();
        break;

    case Game::GameState::WAVE_CLEAR:
        goTitle = StageClearUpdate();
        break;
        /*
    case Game::GameState::GAME_CLEAR:
        goTitle = GameClearUpdate();
        break;
        */
    default:
        break;
    }

    if (goTitle)
    {
        return new WorldMap();
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

    case Game::GameState::PAUSE:
        //GamingDraw();
        PauseDraw();
        break;

    case Game::GameState::GAME_OVER:
        GameOverDraw();
        break;

    case Game::GameState::WAVE_CLEAR:
        StageClearDraw();
        break;
        /*
    case Game::GameState::GAME_CLEAR:
        GameClearDraw();
        break;
        */
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
    _fadingout = true;
    _bgm.Stop();


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
        Debug::DrawString(Vector2D(200, 200), "GAME OVER", ColorPalette::RED4);
    }
    if (_fadeoutCount > 200) {
        Debug::DrawString(Vector2D(200, 400), "左クリックで戻る", ColorPalette::WHITE4);
    }
}


bool Game::StageClearUpdate() {

    if (_fadeoutCount < _fadingInterval)
    {
        _fadeoutCount++;
        return false;
    }

    if (_fadeoutCount == _fadingInterval)
        _fadingout = MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L);

    if (!_fadingout)
        return false;

    _fadeoutCount++;
    if (_fadeoutCount == _fadeoutInterval)
    {
        //TODO : game^3が終わったらコメントアウトを外す
        //Clear();
        //Init();
        return true;
    }

    return false;
}

void Game::StageClearDraw() {

    double blend = double(_fadeoutCount) * 17 / 10;

    if (!_fadingout) {
        if (blend > 150) {
            blend = 150;
        }
    }
    else {
        blend = 150 + 105 * (static_cast<double>(_fadeoutCount - _fadingInterval) / static_cast<double>(_fadeoutInterval - _fadingInterval));
    }

    auto color = Color4(0, 0, 0, 1.0 * blend / 255);
    Debug::DrawRectWithSize(Vector2D(0, 0), Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT), color, true);

    if (_fadeoutCount >= 150
        && _fadeoutCount <= _fadingInterval) {
        Debug::DrawString(Vector2D(200, 200), "ステージクリア", ColorPalette::WHITE4);
    }
    if (_fadeoutCount == _fadingInterval) {
        Debug::DrawString(Vector2D(200, 400), "左クリックで戻る", ColorPalette::WHITE4);
    }
}

/*
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
        Debug::DrawString(Vector2D(200, 200), "ゲームクリア", ColorPalette::WHITE4);
    }
    if (_fadeoutCount > _fadingInterval) {
        Debug::DrawString(Vector2D(200, 400), "左クリックで戻る", ColorPalette::WHITE4);
    }
}
*/

bool Game::GameReadyUpdate()
{
    if (_fadingout)
    {
        if (_fadeoutCount < _fadeinInterval)
            _fadeoutCount++;
        else
            _fadingout = false;

        return false;
    }

    if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) 
    {
        _state = GameState::GAMING;
        _fadeoutCount = 0;
        _bgm.Play();
        return true;
    }

    return false;

}

void Game::GameReadyDraw(){

    double blend = 0.3 * (_fadeinInterval - _fadeoutCount) / _fadeinInterval + 0.7;
    auto color = Color4(0, 0, 0, blend);
    Debug::DrawRectWithSize(Vector2D(0, 0), Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT), color, true);

    if (_fadeinInterval <= _fadeoutCount)
        Debug::DrawString(Vector2D(200, 200), "左クリックで開始", ColorPalette::WHITE4);
}

void Game::GamingUpdate()
{
    if (_dungeon->HasClear())
    {
        //if (_stageNumber < 3)
        //{
        //    _stageNumber++;
            _state = GameState::WAVE_CLEAR;
            return;
        //}
        //else
        //{
        //    _state = GameState::GAME_CLEAR;
        //    _bgm.Stop();
        //    return;
        //}
    }

    if (!_bgm.IsPlaying())
        _bgm.Play();

    if (_dungeon->HasGameOver())
    {
        _state = GameState::GAME_OVER;
        _bgm.Stop();
    }
    _dungeon->Update();

    if (KEYBOARD->ButtonDown(KeyInput::KeyType::KEY_ESCAPE))
        _state = GameState::PAUSE;
}

void Game::GamingDraw()
{
    _dungeon->Draw();
}

bool Game::PauseUpdate()
{
    if (KEYBOARD->ButtonDown(KeyInput::KeyType::KEY_ESCAPE))
        _state = GameState::GAMING;

    auto backColor = Color4(0, 0, 0, 0.9f);
    Debug::DrawRectWithSize(Vector2D(0, 0), Vector2D(WINDOW_WIDTH, WINDOW_HEIGHT), backColor, true);

    Vector2D center(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
    Vector2D frameSize(WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 8.0);

    auto frameColor = ColorPalette::WHITE4;
    Vector2D upperPannelPos(center._x - frameSize._x / 2.0, center._y - frameSize._y / 1.5);
    Vector2D lowerPannelPos(center._x - frameSize._x / 2.0, center._y + frameSize._y / 1.5);

    int fontSize = 32;
    Debug::DrawString(upperPannelPos + frameSize * 0.5 - Vector2D(fontSize * 2.5, fontSize / 2), "ゲームに戻る", ColorPalette::WHITE4, 24);
    Debug::DrawString(lowerPannelPos + frameSize * 0.5 - Vector2D(fontSize * 3.5, fontSize / 2), "ステージ選択に戻る", ColorPalette::WHITE4, 24);

    Debug::DrawRectWithSize(upperPannelPos, frameSize, frameColor, false);
    Debug::DrawRectWithSize(lowerPannelPos, frameSize, frameColor, false);

    auto mousePos = MOUSE->GetCursorPos();
    bool mouseOnUpperPannel =
        (upperPannelPos._x < mousePos._x
            &&  upperPannelPos._y < mousePos._y
            &&  mousePos._x < upperPannelPos._x + frameSize._x
            &&  mousePos._y < upperPannelPos._y + frameSize._y);

    bool mouseOnLowerPannel =
        (lowerPannelPos._x < mousePos._x
            &&  lowerPannelPos._y < mousePos._y
            &&  mousePos._x < lowerPannelPos._x + frameSize._x
            &&  mousePos._y < lowerPannelPos._y + frameSize._y);

    auto fillColor = Color4(1.0f, 1.0f, 1.0f, 0.5f);
    Debug::DrawRectWithSize(upperPannelPos, frameSize, fillColor, mouseOnUpperPannel);
    Debug::DrawRectWithSize(lowerPannelPos, frameSize, fillColor, mouseOnLowerPannel);

    if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
    {
        if (mouseOnUpperPannel)
        {
            _state = GameState::GAMING;
        }
        else if (mouseOnLowerPannel)
        {
            return true;
        }
    }

    return false;
}

void Game::PauseDraw()
{
}