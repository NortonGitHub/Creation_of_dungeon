#pragma once
#include "SceneBase.h"
class Result :
    public SceneBase
{
public:
    Result();
    ~Result();

    SceneBase* Update();
    void Draw();
};

