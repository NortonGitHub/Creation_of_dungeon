#pragma once
#include "SceneBase.h"
class Map :
    public SceneBase
{
public:
    Map();
    ~Map();

    SceneBase* Update();
    void Draw();

    std::string GetClassName() const {
        return class_name;
    }

private:
    std::string class_name;
};

