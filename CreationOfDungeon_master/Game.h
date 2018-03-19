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

    //‰‰o—p‚ÌˆÃ“]ŠÔ
    const int _fadeinInterval;  //ˆÃ“]‚©‚ç“r’†‚Ü‚Å
    const int _fadingInterval; //’Êí‚©‚ç“r’†‚Ü‚Å
    const int _fadeoutInterval; //“r’†‚©‚çˆÃ“]‚Ü‚Å

    //‰‰o—p‚ÌˆÃ“]ƒJƒEƒ“ƒg
    int _fadeoutCount;
    bool _fadingout;

    //‚±‚±‚©‚ç‰º‚ª’Ç‰Á‚µ‚½•”•ª(negative)
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

    // TODO : ‚ ‚Æ‚Åpointer‚É‚¹‚¸‚Æ‚àÏ‚Ş‚æ‚¤‚É‚·‚é
    Dungeon* _dungeon;
    std::string _stageNumber;
	std::string _areaNumber;

    bool isBoss;

	GameResult gameResult;

	Sprite _black;

};

