#include "MapTile.h"
#include "TiledObject.h"
#include "TileField.h"
#include "AI/Breadcrumb.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

MapTile::MapTile(int col, int row)
: _tilePos(row, col)
, _breadcrumb(nullptr)
{
}

MapTile::MapTile(TiledVector pos)
: _tilePos(pos)
, _breadcrumb(nullptr)
{
}


MapTile::~MapTile()
{
}


void MapTile::Init()
{
    //¶‚Æ‰E‚ªì‚È‚ç
    std::string fileName = "graph/background/";
    if ((FIELD->GetRawNumber(_tilePos + TiledVector(-1, 0)) == 6)
        && (FIELD->GetRawNumber(_tilePos + TiledVector(1, 0)) == 6)
        && (FIELD->GetRawNumber(_tilePos + TiledVector(0, 1)) == 0)
        && (FIELD->GetRawNumber(_tilePos + TiledVector(0, -1)) == 0))
    {
        fileName += "bridge_v";
    }
    else if ((FIELD->GetRawNumber(_tilePos + TiledVector(0, -1)) == 6)
        && (FIELD->GetRawNumber(_tilePos + TiledVector(0, 1)) == 6)
        && (FIELD->GetRawNumber(_tilePos + TiledVector(1, 0)) == 0)
        && (FIELD->GetRawNumber(_tilePos + TiledVector(-1, 0)) == 0))
    {
        fileName += "bridge_h";
    }
    else
    {
        fileName += "ground";
    }

    fileName += ".png";

    _graph.Load(fileName);
    _graph.SetPosition(_tilePos.GetWorldPos());
    _graph.SetPriority(-2);
    _graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
}


TiledObject* MapTile::GetTiledObject() const
{
    if (_objects.size() == 0)
        return nullptr;
    
    return _objects[_objects.size() - 1];
}


bool MapTile::IsRegistable(TiledObject& obj) const
{
    //“o˜^‚³‚ê‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚ª‚·‚×‚Äã‘‚«‰Â”\‚È‚à‚Ì‚È‚ç“o˜^‚Å‚«‚é
    for (auto object : _objects)
    {
        if (!object->IsOverwritable(&obj))
            return false;
    }

    return true;
}


void MapTile::Regist(TiledObject* obj)
{
    _objects.push_back(obj);
    obj->SetTile(this);
}


void MapTile::Remove(TiledObject* obj)
{
    auto it = std::find(_objects.begin(), _objects.end(), obj);
    if (it != _objects.end())
    {
        _objects.erase(it);
        obj->SetTile(nullptr);
    }
}


void MapTile::Regist(Breadcrumb* crumb)
{
    _breadcrumb = crumb;
}


void MapTile::Remove(Breadcrumb* crumb)
{
    _breadcrumb = nullptr;
}


void MapTile::Draw()
{
    _position = GetTilePos().GetWorldPos() + Vector2D(FIELD_OFFSET_X, FIELD_OFFSET_Y);

    /*
    Debug::DrawRectWithSize(_position
                     , Vector2D(TILE_SIZE, TILE_SIZE)
                     , Color4(0.0, 0.0, 0.0, 1.0)
                     , false);
    */

    if (_breadcrumb != nullptr)
        _breadcrumb->Update();
    
    if (_breadcrumb != nullptr)
        _breadcrumb->Draw();
}