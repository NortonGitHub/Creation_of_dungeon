#include "Map.h"



Map::Map()
{
    class_name = "map";
}


Map::~Map()
{
}

SceneBase * Map::Update()
{
    return nullptr;
}

SceneBase * Map::Update(UIManager _ui)
{
    _ui.Update();
    return this;
}

void Map::Draw()
{
}
