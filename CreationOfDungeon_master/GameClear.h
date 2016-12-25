#pragma once
#include "SceneBase.h"
class GameClear :
    public SceneBase
{
public:
    GameClear();
    ~GameClear();

    SceneBase* Update();
    SceneBase* Update(UIManager _ui);
    void Draw();
    std::string GetClassNameData() const {
        return class_name;
    }

private:
    std::string class_name;
};

