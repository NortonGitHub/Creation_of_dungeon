#pragma once
#include "SceneBase.h"
#include "MapProcessManager.h"
#include "CharaManager.h"

class Game :
    public SceneBase
{
public:
    Game();
    ~Game();

    SceneBase* Update();
    void Draw();

private:

    std::string stage_num;

    CharaManager chara_manager;

    MapProcessManager map_process_manager;

    MouseContent mouse_status;


    //ここから下が追加した部分(negative)
    bool isGameOver;    //デバッグとしてとりあえず追加。ゲームオーバーしているかどうか。trueでゲームオーバーしている
    int gameOverCount;  //ゲームオーバーの処理を始めてから進んだフレーム数

    bool GameOverUpdate();
    void GameOverDraw();

    //ここから下が追加した部分(negative)
    bool isStageClear;    //デバッグとしてとりあえず追加。ステージをクリアしているかどうか。trueでステージをクリアしている
    int StageClearCount;  //ステージのクリアの処理を始めてから進んだフレーム数

    bool StageClearUpdate();
    void StageClearDraw();

    //ここから下が追加した部分(negative)
    bool isGameClear;    //デバッグとしてとりあえず追加。ゲームをクリアしているかどうか。trueでゲームをクリアしている
    int GameClearCount;  //ゲームのクリアの処理を始めてから進んだフレーム数

    bool GameClearUpdate();
    void GameClearDraw();

};

