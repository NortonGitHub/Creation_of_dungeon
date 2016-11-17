#pragma once
#include <memory>
#include <vector>
#include "MapBase.h"
#include "MouseContent.h"


class MapProcessManager
{
public:
    MapProcessManager();
    MapProcessManager(std::string stage_num);
    ~MapProcessManager();

    void Update(MouseContent mc);
    void Draw();

private:

    std::vector<std::shared_ptr<MapData>> staticMap;    //下地となるマップデータ
    std::vector<std::shared_ptr<MapData>> dynamicMap;   //オブジェクト設置の際に座標を書き換えるマップデータ
};

