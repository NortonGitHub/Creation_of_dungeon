#pragma once
#include "SceneBase.h"
class GameClear :
    public SceneBase
{
public:
    GameClear();
    ~GameClear();

    SceneBase* Update();
    void Draw();
    std::string GetClassName() const {
        return class_name;
    }

private:
    std::string class_name;
};

