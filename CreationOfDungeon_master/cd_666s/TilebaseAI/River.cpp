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

    //¶‚ªì‚È‚ç
    if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
    {
        //ã‚ªì‚È‚ç
        if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
            fileName += "river_corner_lr";
        //‰º‚ªì‚È‚ç
        else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
            fileName += "river_corner_ur";
        else
            fileName += "river_h";
    }
    //‰E‚ªì‚È‚ç
    else if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
    {
        //ã‚ªì‚È‚ç
        if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
            fileName += "river_corner_ll";
        //‰º‚ªì‚È‚ç
        else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
            fileName += "river_corner_ul";
        else
            fileName += "river_h";
    }
    //‰º‚ªì‚È‚ç
    else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
    {
        //‰E‚ªì‚È‚ç
        if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
            fileName += "river_corner_ll";
        //¶‚ªì‚È‚ç
        else if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
            fileName += "river_corner_lr";
        else
            fileName += "river_v";
    }
    //ã‚ªì‚È‚ç
    else if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
    {
        //‰E‚ªì‚È‚ç
        if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
            fileName += "river_corner_ul";
        //¶‚ªì‚È‚ç
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