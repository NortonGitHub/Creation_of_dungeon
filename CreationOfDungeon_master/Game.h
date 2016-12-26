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


    //�������牺���ǉ���������(negative)
    bool isGameOver;    //�f�o�b�O�Ƃ��ĂƂ肠�����ǉ��B�Q�[���I�[�o�[���Ă��邩�ǂ����Btrue�ŃQ�[���I�[�o�[���Ă���
    int gameOverCount;  //�Q�[���I�[�o�[�̏������n�߂Ă���i�񂾃t���[����

    bool GameOverUpdate();
    void GameOverDraw();

    //�������牺���ǉ���������(negative)
    bool isStageClear;    //�f�o�b�O�Ƃ��ĂƂ肠�����ǉ��B�X�e�[�W���N���A���Ă��邩�ǂ����Btrue�ŃX�e�[�W���N���A���Ă���
    int StageClearCount;  //�X�e�[�W�̃N���A�̏������n�߂Ă���i�񂾃t���[����

    bool StageClearUpdate();
    void StageClearDraw();

    //�������牺���ǉ���������(negative)
    bool isGameClear;    //�f�o�b�O�Ƃ��ĂƂ肠�����ǉ��B�Q�[�����N���A���Ă��邩�ǂ����Btrue�ŃQ�[�����N���A���Ă���
    int GameClearCount;  //�Q�[���̃N���A�̏������n�߂Ă���i�񂾃t���[����

    bool GameClearUpdate();
    void GameClearDraw();

};

