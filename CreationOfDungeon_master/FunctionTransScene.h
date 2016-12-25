#pragma once
#include "SceneBase.h"

class FunctionTransScene
{
public:
    FunctionTransScene() = delete;
    ~FunctionTransScene();

    static SceneBase* GetSceneBase(std::string scene_name);

};

