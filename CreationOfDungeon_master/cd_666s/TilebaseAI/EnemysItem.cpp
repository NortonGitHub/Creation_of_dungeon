#include "EnemysItem.h"
#include "Enemy.h"
#include "TiledVector.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"

EnemysItem::EnemysItem(std::unique_ptr<Equipment> contents, TiledVector tilePos)
: TiledObject(tilePos)
, _contents(std::move(contents))
, _countAfterEmpty(0)
{
    _type = TiledObject::Type::ITEM;
    _graph.Load("resourse/graph/background/treasure01.png");
    _contentsGraph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
    _contentsGraph.SetResource(_contents->_image);
    _contentsGraph.SetPriority(5);
    _contentsGraph.SetDisplayMode(false);
}


EnemysItem::~EnemysItem()
{
}


void EnemysItem::LoadItem(int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects, std::string fileName)
{
    //アイテムを生成して宝箱内にセット
   auto param = std::make_unique<Equipment>(BattleParameter(0, 0, 0, 10, 15, 0), 100);
   objects.push_back(std::make_shared<EnemysItem>(std::move(param), TiledVector(countX, countY)));
}


void EnemysItem::Update()
{
    if (_contents != nullptr)
        return;

    _countAfterEmpty++;
    if (_countAfterEmpty < 60)
    {
        if (60 / 2 < _countAfterEmpty)
            return;

        auto currentPos = _position;
        currentPos -= {0, TILE_SIZE * 1.5 * (_countAfterEmpty / 60.0) * TILE_SIZE / 32.0};
        _contentsGraph.SetPosition(currentPos);
    }
    else
    {
        OBJECT_MGR->Remove(this);
    }
}


void EnemysItem::Draw()
{
    if (!IsEnable())
        return;

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
    _contentsGraph.SetDisplayMode(true);
    //OBJECT_MGR->Remove(this);
}


bool EnemysItem::IsEnable() const
{
    return (_contents != nullptr);
}