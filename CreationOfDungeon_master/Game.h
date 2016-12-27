#pragma once
#include "SceneBase.h"
#include "MapProcessManager.h"
#include "CharaManager.h"
#include "cd_666s/TilebaseAI/Dungeon.h"

class Game :
    public SceneBase
{
public:
    Game();
    ~Game();

    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    };

private:
    std::string class_name;

    std::string stage_num;

    CharaManager chara_manager;

    MapProcessManager map_process_manager;

    MouseContent mouse_status;

    std::vector<std::string> _functions;

    Graph test;

    //negative==================================
    enum class GameState
    {
        READY,
        GAMING,
        GAME_OVER,
        WAVE_CLEAR,
        GAME_CLEAR
    };
    GameState _state;
    //演出用の暗転カウント
    int _fadeoutCount;

    //ここから下が追加した部分(negative)
    bool GameOverUpdate();
    void GameOverDraw();

    bool StageClearUpdate();
    void StageClearDraw();
    bool GameClearUpdate();
    void GameClearDraw();


    //666=======================================
    bool GameReadyUpdate();
    void GameReadyDraw();

    void Init();
    void Clear();

    void GamingUpdate();
    void GamingDraw();

    // TODO : あとでpointerにせずとも済むようにする
    Dungeon* _dungeon;
    int _stageNumber;
};

