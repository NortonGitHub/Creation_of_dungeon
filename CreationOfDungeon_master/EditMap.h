#pragma once
#include "SceneBase.h"
class EditMap :
    public SceneBase
{
public:
    EditMap();
    ~EditMap();

    SceneBase* Update();
    void Draw();

    std::string GetClassName() const {
        return class_name;
    }

private:
    std::string class_name;
};

