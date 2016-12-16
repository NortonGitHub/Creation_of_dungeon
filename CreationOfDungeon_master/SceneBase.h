#pragma once
#include "UIManager.h"
#include <string>

class SceneBase
{
public:
    SceneBase();
    ~SceneBase();

    void Init(std::string _class_name);

    SceneBase* MainUpdate();
    void MainDraw();
    
    virtual std::string GetClassName() const = 0;

    virtual SceneBase* Update() = 0;
    virtual void Draw() = 0;

private:
    SceneBase* now_scene;

protected:

    UIManager ui_manager;

    Vector2D _before_pos;

};

