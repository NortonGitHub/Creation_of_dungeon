#include "River.h"
#include "TileField.h"
#include "../Resources//ResourceManager.h"
#include "../DebugDraw.h"

River::River(TiledVector tilePos)
    : Obstacle(tilePos)
{
}


River::~River()
{
}


void River::Init()
{
    auto tilePos = GetTilePos();
    auto fieldType = GetTile().lock()->GetFieldType();
    std::string fileName = GetMapChipGraphDirectory(fieldType);

    //左が川なら
    if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
    {
        //上が川なら
        if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
            fileName += "river_corner_lr";
        //下が川なら
        else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
            fileName += "river_corner_ur";
        else
            fileName += "river_h";
    }
    //右が川なら
    else if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
    {
        //上が川なら
        if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
            fileName += "river_corner_ll";
        //下が川なら
        else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
            fileName += "river_corner_ul";
        else
            fileName += "river_h";
    }
    //下が川なら
    else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
    {
        //右が川なら
        if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
            fileName += "river_corner_ll";
        //左が川なら
        else if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
            fileName += "river_corner_lr";
        else
            fileName += "river_v";
    }
    //上が川なら
    else if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
    {
        //右が川なら
        if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
            fileName += "river_corner_ul";
        //左が川なら
        else if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
            fileName += "river_corner_ur";
        else
            fileName += "river_v";
    }
    else
    {
        fileName += "river_v";
    }

    _graph.Load(fileName + ".png");
    _graph.SetPosition(tilePos.GetWorldPos());
    TiledObject::Init();
}