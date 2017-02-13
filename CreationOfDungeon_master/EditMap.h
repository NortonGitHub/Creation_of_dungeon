#pragma once
#include "SceneBase.h"
#include "MakeDungeon.h"
class EditMap :
    public SceneBase
{
public:
    EditMap(std::string _stage_num);
    ~EditMap();

    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    }

    void Init();

private:
    std::string class_name;

    UIManager _uiManager;

    std::string stage_num;

    std::shared_ptr<MakeDungeon> _dungeon;
};

