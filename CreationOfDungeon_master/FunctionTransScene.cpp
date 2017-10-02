#include "FunctionTransScene.h"
#include "Game.h"
#include "Title.h"
#include "WorldMap.h"
#include "GameClear.h"
#include "GameOver.h"

FunctionTransScene::~FunctionTransScene()
{
}

SceneBase * FunctionTransScene::GetSceneBase(std::string scene_name)
{
    if (scene_name.find("game_1") != std::string::npos) {
        return new Game("1");
    }
    else if (scene_name.find("world_map") != std::string::npos) {
        return new WorldMap();
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
