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
    auto fieldType = GetTile().lock()->GetFieldType();
    std::string fileName = GetMapChipGraphDirectory(fieldType);
    fileName += GetNameFromAroundInfo(tilePos);

    _graph.Load(fileName + ".png");
    _graph.SetPosition(tilePos.GetWorldPos());
    TiledObject::Init();
}


std::string Obstacle::GetNameFromAroundInfo(TiledVector tilePos)
{
    //下が川なら
    if (!FIELD->IsInside(tilePos + TiledVector(0, -1)))
    {
        if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
            return "wall_side_f_river";
    }

    //下がフィールド外なら
    if (!FIELD->IsInside(tilePos + TiledVector(0, -1)))
    {
        if (!FIELD->IsInside(tilePos + TiledVector(1, 0)))
        {
            return "wall_side_lf";
        }
        else if (!FIELD->IsInside(tilePos + TiledVector(-1, 0)))
        {
            return "wall_side_rf";
        }
        else
        {
            return "wall_side_f";
        }
    }
    if (!FIELD->IsInside(tilePos + TiledVector(0, 1)))
    {
        if (!FIELD->IsInside(tilePos + TiledVector(1, 0)))
        {
            return "wall_side_lb";
        }
        else if (!FIELD->IsInside(tilePos + TiledVector(-1, 0)))
        {
            return "wall_side_rb";
        }
        else
        {
            //上が川でその左右が川でなければ
            if ((FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
                && (FIELD->GetRawNumber(tilePos + TiledVector(-1, -1)) != 6)
                && (FIELD->GetRawNumber(tilePos + TiledVector(1, -1)) != 6))
                return "wall_side_b_river";

            return "wall_side_b";
        }
    }
    if (!FIELD->IsInside(tilePos + TiledVector(1, 0)))
    {
        //左が川でその上下が川なら
        if ((FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
            && (FIELD->GetRawNumber(tilePos + TiledVector(-1, 1)) != 6)
            && (FIELD->GetRawNumber(tilePos + TiledVector(-1, -1)) != 6))
            return "wall_side_l_river";

        return "wall_side_l";
    }
    if (!FIELD->IsInside(tilePos + TiledVector(-1, 0)))
    {
        //右が川でその上下がなら
        if ((FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
            && (FIELD->GetRawNumber(tilePos + TiledVector(1, 1)) != 6)
            && (FIELD->GetRawNumber(tilePos + TiledVector(1, -1)) != 6))
            return "wall_side_r_river";

        return "wall_side_r";
    }

    return "rock01";
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