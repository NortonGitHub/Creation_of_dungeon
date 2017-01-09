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
    std::string fileName = "resourse/graph/background/";

    //������Ȃ�
    if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
    {
        //�オ��Ȃ�
        if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
            fileName += "river_corner_lr";
        //������Ȃ�
        else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
            fileName += "river_corner_ur";
        else
            fileName += "river_h";
    }
    //�E����Ȃ�
    else if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
    {
        //�オ��Ȃ�
        if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
            fileName += "river_corner_ll";
        //������Ȃ�
        else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
            fileName += "river_corner_ul";
        else
            fileName += "river_h";
    }
    //������Ȃ�
    else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
    {
        //�E����Ȃ�
        if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
            fileName += "river_corner_ll";
        //������Ȃ�
        else if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
            fileName += "river_corner_lr";
        else
            fileName += "river_v";
    }
    //�オ��Ȃ�
    else if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
    {
        //�E����Ȃ�
        if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
            fileName += "river_corner_ul";
        //������Ȃ�
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