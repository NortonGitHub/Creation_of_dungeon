#include "EnemysItem.h"
#include "Enemy.h"
#include "TiledVector.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"

EnemysItem::EnemysItem(std::unique_ptr<Equipment> contents, TiledVector tilePos)
: TiledObject(tilePos)
, _contents(std::move(contents))
{
    _type = TiledObject::Type::ITEM;
    _graph.Load("resourse/graph/background/treasure01.png");
}


EnemysItem::~EnemysItem()
{
}


void EnemysItem::LoadItem(int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects, std::string fileName)
{
    //アイテムを生成して宝箱内にセット
   auto param = std::make_unique<Equipment>(BattleParameter(0, 10, 15, 0), 100);
   objects.push_back(std::make_shared<EnemysItem>(std::move(param), TiledVector(countX, countY)));
}


void EnemysItem::Update()
{
}


void EnemysItem::Draw()
{
    if (!IsEnable())
        return;

    //_graph.SetDisplayMode(_isEnable);
    _position = GetTilePos().GetWorldPos();
    GraphicalObject::Draw();
}


bool EnemysItem::IsOverwritable(TiledObject* overwriter)
{
    return true;
}


void EnemysItem::Interact(Character& character)
{
    OBJECT_MGR->Remove(this);
}


void EnemysItem::GiveItem(Enemy& enemy)
{
    enemy.SetItem(std::move(_contents));
}


bool EnemysItem::IsEnable() const
{
    return (_contents != nullptr);
}