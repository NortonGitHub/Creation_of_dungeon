#pragma once
#include "SceneBase.h"
#include "MouseManager.h"

class Title :
    public SceneBase
{
public:
    Title();
    ~Title();

    SceneBase* Update();
    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    }

private:
    std::string stage_num;

    MouseContent mouse_status;

    std::string class_name;

    Graph test;
};

