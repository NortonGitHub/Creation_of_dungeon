#pragma once
#include "Scenebase.h"

class FunctionTransScene
{
public:
    FunctionTransScene() = delete;
    ~FunctionTransScene();

    static SceneBase* GetSceneBase(std::string scene_name);

};

