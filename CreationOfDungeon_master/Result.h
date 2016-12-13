#pragma once
#include "SceneBase.h"
class Result :
    public SceneBase
{
public:
    Result();
    ~Result();

    SceneBase* Update();
    void Draw();

    std::string GetClassName() const {
        return class_name;
    }

private:
    std::string class_name;
};

