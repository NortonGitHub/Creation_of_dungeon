#include "EditMap.h"



EditMap::EditMap(std::string _stage_num)
    : stage_num(_stage_num)
{
    class_name = "edit";
    Init();
}


EditMap::~EditMap()
{
}

SceneBase * EditMap::Update(UIManager _ui)
{
    _dungeon->Update();

    return this;
}

void EditMap::Draw()
{
    _dungeon->Draw();
}

void EditMap::Init()
{
    _dungeon = std::make_shared<MakeDungeon>();
}
