#pragma once
#include "SceneBase.h"
class EditMap :
    public SceneBase
{
public:
    EditMap();
    ~EditMap();

    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    }

private:
    std::string class_name;
};

