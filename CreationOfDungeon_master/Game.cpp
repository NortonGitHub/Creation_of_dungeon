#include "Game.h"
#include "MouseManager.h"
#include "Title.h"
#include "DxLib.h"


Game::Game()
    :stage_num("1-1"),
    mouse_status(MouseContent())
{


    chara_manager = CharaManager(stage_num);


    //ここから追加 by negative
    gameOverCount = 0;
    isGameOver = false;
    
}


Game::~Game()
{
}

SceneBase * Game::Update()
{

    mouse_status = MouseManager::GetMouseStatus(mouse_status);
    
    if (mouse_status._mouse_left_click) {
        if (isGameOver == false && isStageClear == false && isGameClear == false) {
            isGameOver = true;
        }
    }
    if (mouse_status._mouse_right_click) {
        if (isGameOver == false && isStageClear == false && isGameClear == false) {
            isStageClear = true;
        }
    }
    if (mouse_status._mouse_middle_click) {
        if (isGameOver == false && isStageClear == false && isGameClear == false) {
            isGameClear = true;
        }
    }

    if (isGameOver == true) {
        bool goTitle = GameOverUpdate();
        if (goTitle == true) {
            return new Title();
        }
        else {
            return this;
        }
    }

    if (isStageClear == true) {
        bool goTitle = StageClearUpdate();
        if (goTitle == true) {
            return new Title();
        }
        else {
            return this;
        }
    }

    if (isGameClear == true) {
        bool goTitle = GameClearUpdate();
        if (goTitle == true) {
            return new Title();
        }
        else {
            return this;
        }
    }

    chara_manager.Update(mouse_status);

    map_process_manager.Update(mouse_status);
    
    return this;
}

void Game::Draw()
{


    DrawBox(0, 0, 1024, 768, GetColor(255, 255, 255), TRUE);
    DrawBox(0, 0, 124, 268, GetColor(255, 0, 255), TRUE);
    DrawBox(300, 288, 524, 548, GetColor(255, 255, 0), TRUE);

    


    chara_manager.Draw();

    map_process_manager.Draw();


    if (isGameOver == true) {

        GameOverDraw();

    }
    if (isStageClear == true) {

        StageClearDraw();

    }
    if (isGameClear == true) {

        GameClearDraw();

    }

}


bool Game::GameOverUpdate() {

    
    gameOverCount++;

    if (gameOverCount > 200 && mouse_status._mouse_left_click) {

        return true;

    }

    return false;

}

void Game::GameOverDraw() {

    double blend = double(gameOverCount)*17/10;

    if (blend > 150) {
        blend = 150;
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
    DrawBox(0, 0, 1024, 768, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    
    if (gameOverCount > 150) {
        DrawFormatString(200, 200, GetColor(255, 0, 0), "ガメオベラ");
    }
    if (gameOverCount > 200) {
        DrawFormatString(200, 400, GetColor(255, 255, 255), "左クリックで戻る");
    }

}

bool Game::StageClearUpdate() {

    StageClearCount++;

    if (StageClearCount > 200 && mouse_status._mouse_left_click) {

        return true;

    }

    return false;

}

void Game::StageClearDraw() {

    double blend = double(StageClearCount) * 17 / 10;

    if (blend > 150) {
        blend = 150;
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
    DrawBox(0, 0, 1024, 768, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    if (StageClearCount > 150) {
        DrawFormatString(200, 200, GetColor(255, 0, 0), "ステージクリア");
    }
    if (StageClearCount > 200) {
        DrawFormatString(200, 400, GetColor(255, 255, 255), "左クリックで戻る");
    }

}

bool Game::GameClearUpdate() {

    GameClearCount++;

    if (GameClearCount > 200 && mouse_status._mouse_left_click) {

        return true;

    }

    return false;

}

void Game::GameClearDraw() {

    double blend = double(GameClearCount) * 17 / 10;

    if (blend > 150) {
        blend = 150;
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
    DrawBox(0, 0, 1024, 768, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    if (GameClearCount > 150) {
        DrawFormatString(200, 200, GetColor(255, 0, 0), "ゲームクリア");
    }
    if (GameClearCount > 200) {
        DrawFormatString(200, 400, GetColor(255, 255, 255), "左クリックで戻る");
    }

}

