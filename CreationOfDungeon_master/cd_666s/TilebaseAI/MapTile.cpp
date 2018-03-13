#include "MapTile.h"
#include "TiledObject.h"
#include "TileField.h"
#include "AI/Breadcrumb.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

MapTile::MapTile(int col, int row)
: _tilePos(row, col)
, _breadcrumb(nullptr)
, _rawNumber(0)
, _type(FieldType::None)
{
}

MapTile::MapTile(TiledVector pos)
: _tilePos(pos)
, _breadcrumb(nullptr)
, _rawNumber(0) 
, _type(FieldType::None) 
{
}


MapTile::~MapTile()
{
}


void MapTile::Init()
{
    //左と右が川なら
    std::string fileName = GetMapChipGraphDirectory(_type);
	/*
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
	*/

	fileName += "ground";

    fileName += ".png";

    _graph.Load(fileName);
    _graph.SetPosition(_tilePos.GetWorldPos());
    _graph.SetPriority(Sprite::Priority::FIELD_BASE);
    _graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
}


void MapTile::SetFieldType(std::string data, FieldType defaultType)
{
    //文字列からタイプに変換
    _type = GetFieldTypeFromData(data);

    //変換できなかったらデフォルト
    if (_type == FieldType::None)
        _type = defaultType;
}


bool MapTile::IsRegistable(TiledObject& obj) const
{
    //登録されているオブジェクトがすべて上書き可能なものなら登録できる
    for (auto object : _objects)
    {
        if (!object->IsOverwritable(&obj))
            return false;
    }

    return true;
}


void MapTile::Regist(TiledObject* obj, std::weak_ptr<MapTile> tile)
{
    tile.lock()->_objects.push_back(obj);
    obj->SetTile(tile);
}


void MapTile::Remove(TiledObject* obj, std::weak_ptr<MapTile> tile)
{
    auto& objects = tile.lock()->_objects;
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end())
    {
        objects.erase(it);
        obj->SetTile(tile);
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

    if (_breadcrumb != nullptr)
        _breadcrumb->Update();
    
    if (_breadcrumb != nullptr)
        _breadcrumb->Draw();
}