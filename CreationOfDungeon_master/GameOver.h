#pragma once
#include "SceneBase.h"
class GameOver :
    public SceneBase
{
public:
    GameOver();
    ~GameOver();

    SceneBase* Update();
    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    }

private:
    std::string class_name;
};

