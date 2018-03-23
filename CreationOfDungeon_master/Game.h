#pragma once
#include "SceneBase.h"
#include "cd_666s/Sound/Sound.h"
#include "cd_666s/TilebaseAI/Dungeon.h"
#include "GameResult.h"

class Game : public SceneBase
{
public:
	Game(std::string areaNum, std::string stageNumber);
    ~Game();

    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    };

private:
    std::string class_name;

    std::string stage_num;

    std::vector<std::string> _functions;

    Graph test;
    Sound _bgm;

    //negative==================================
    enum class GameState
    {
        READY,
        GAMING,
        GAME_OVER,
        WAVE_CLEAR,
        //GAME_CLEAR,
        PAUSE
    };
    GameState _state;

    //���o�p�̈Ó]����
    const int _fadeinInterval;  //�Ó]����r���܂�
    const int _fadingInterval; //�ʏ킩��r���܂�
    const int _fadeoutInterval; //�r������Ó]�܂�

    //���o�p�̈Ó]�J�E���g
    int _fadeoutCount;
    bool _fadingout;

    //�������牺���ǉ���������(negative)
    bool GameOverUpdate();
    void GameOverDraw();

    bool StageClearUpdate();
    void StageClearDraw();
    //bool GameClearUpdate();
    //void GameClearDraw();


    //666=======================================
    bool GameReadyUpdate();
    void GameReadyDraw();

    void Init();
    void Clear();

    void GamingUpdate();
    void GamingDraw();

    bool PauseUpdate();
    void PauseDraw();

    // TODO : ���Ƃ�pointer�ɂ����Ƃ��ςނ悤�ɂ���
    Dungeon* _dungeon;
    std::string _stageNumber;
	std::string _areaNumber;

    bool isBoss;

	GameResult gameResult;

	Sprite _black;

};

