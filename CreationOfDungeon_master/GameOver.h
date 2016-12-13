#pragma once
#include "SceneBase.h"
class GameOver :
    public SceneBase
{
public:
    GameOver();
    ~GameOver();

    SceneBase* Update();
    void Draw();

    std::string GetClassName() const {
        return class_name;
    }

private:
    std::string class_name;
};

