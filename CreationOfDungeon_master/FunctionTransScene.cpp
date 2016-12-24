#include "FunctionTransScene.h"
#include "Game.h"
#include "Title.h"
#include "Map.h"
#include "GameClear.h"
#include "GameOver.h"

FunctionTransScene::~FunctionTransScene()
{
}

SceneBase * FunctionTransScene::GetSceneBase(std::string scene_name)
{
    if (scene_name.find("game") != std::string::npos) {
        return new Game();
    }
    else if (scene_name.find("map") != std::string::npos) {
        return new Map();
    }
    else if (scene_name.find("clear") != std::string::npos) {
        return new GameClear();
    }
    else if (scene_name.find("over") != std::string::npos) {
        return new GameOver();
    }
    else if (scene_name.find("title") != std::string::npos) {
        return new Title();
    }
    return nullptr;
}
