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
    void Draw();

    std::string GetClassName() const {
        return class_name;
    }

private:
    std::string stage_num;

    MouseContent mouse_status;

    std::string class_name;
};

