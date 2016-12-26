#include "Obstacle.h"
#include "TiledVector.h"
#include "TileField.h"
#include "../Resources//ResourceManager.h"
#include "../DebugDraw.h"

Obstacle::Obstacle(TiledVector tilePos)
: TiledObject(tilePos)
{
    _type = TiledObject::Type::BLOCK;
}


Obstacle::~Obstacle()
{
}


void Obstacle::Init()
{
    auto tilePos = GetTilePos();
    std::string fileName = RESOURCE_TABLE->GetFolderPath() + "graph/background/";

    if (!FIELD->IsInside(tilePos + TiledVector(0, -1)))
    {
        if (!FIELD->IsInside(tilePos + TiledVector(1, 0)))
        {
            fileName += "wall_side_lf";
        }
        else if (!FIELD->IsInside(tilePos + TiledVector(-1, 0)))
        {
            fileName += "wall_side_rf";
        }
        else
        {
            fileName += "wall_side_f";
        }
    }
    else if (!FIELD->IsInside(tilePos + TiledVector(0, 1)))
    {
        if (!FIELD->IsInside(tilePos + TiledVector(1, 0)))
        {
            fileName += "wall_side_lb";
        }
        else if (!FIELD->IsInside(tilePos + TiledVector(-1, 0)))
        {
            fileName += "wall_side_rb";
        }
        else
        {
            fileName += "wall_side_b";
        }
    }
    else if (!FIELD->IsInside(tilePos + TiledVector(1, 0)))
    {
        fileName += "wall_side_l";
    }
    else if (!FIELD->IsInside(tilePos + TiledVector(-1, 0)))
    {
        fileName += "wall_side_r";
    }
    else
    {
        fileName += "rock01";
    }


    _graph.Load(fileName + ".png");
    _graph.SetPosition(tilePos.GetWorldPos());
    TiledObject::Init();
}


void Obstacle::Update()
{
}


void Obstacle::Draw()
{
}


bool Obstacle::IsOverwritable(TiledObject* overwriter)
{
    return false;
}