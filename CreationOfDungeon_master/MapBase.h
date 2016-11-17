#pragma once
#include "MapData.h"
#include <vector>
#include <memory>

class MapBase
{
public:
    MapBase();
    ~MapBase();

    void LoadMapData(int _stage_num);

    void GetStaticMap(std::vector<std::shared_ptr<MapData>>& _static) {
        _static = std::move(staticMap); staticMap.at(0);
    }

    void GetDynamicMap(std::vector<std::shared_ptr<MapData>>& _dynamic) {
        _dynamic = std::move(dynamicMap);
    }

private:
    /*
    staticMapの上にdynamicMapを重ね合わせる様に処理並びに描画を行う
    */
    std::vector<std::shared_ptr<MapData>> staticMap;    //下地となるマップデータ
    std::vector<std::shared_ptr<MapData>> dynamicMap;   //オブジェクト設置の際に座標を書き換えるマップデータ

    //std::vector<MapData*> staticMap;  //下地となるマップデータ
    //std::vector<MapData*> dynamicMap; //オブジェクト設置の際に座標を書き換えるマップデータ

};

