#pragma once
#include "UIManager.h"
#include <string>

class SceneBase
{
public:
    SceneBase();
    ~SceneBase();

    SceneBase* MainUpdate();
    
    std::string GetClassName() const {
        return class_name;
    }

    virtual SceneBase* Update() = 0;
    virtual void Draw() = 0;

private:
    SceneBase* now_scene;

protected:

    UIManager ui_manager;

    std::string class_name;

    Vector2D _before_pos;

};

