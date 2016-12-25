#include "EnemysItem.h"
#include "TiledVector.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"

EnemysItem::EnemysItem(TiledVector tilePos)
: TiledObject(tilePos)
, _isEnable(true)
{
    _type = TiledObject::Type::ITEM;
    _graph.Load(RESOURCE_TABLE->GetFolderPath() + "graph/background/treasure01.png");
}


EnemysItem::~EnemysItem()
{
}


void EnemysItem::Update()
{
}


void EnemysItem::Draw()
{
    _graph.SetDisplayMode(_isEnable);
    _position = GetTilePos().GetWorldPos();
    GraphicalObject::Draw();
}


bool EnemysItem::IsOverwritable(TiledObject* overwriter)
{
    return true;
}


void EnemysItem::Interact(Character& character)
{
    _isEnable = false;
    OBJECT_MGR->Remove(this);
}


bool EnemysItem::IsEnable() const
{
    return _isEnable;
}