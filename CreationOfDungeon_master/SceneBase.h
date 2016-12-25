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
    
    virtual std::string GetClassNameData() const = 0;

    virtual SceneBase* Update(UIManager _ui) = 0;
    virtual void Draw() = 0;

private:
    SceneBase* now_scene;

    Graph test;

protected:

    UIManager ui_manager;

    Vector2D _before_pos;

};

