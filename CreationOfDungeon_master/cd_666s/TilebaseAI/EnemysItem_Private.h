#pragma once
#include "EnemysItem.h"
#include "Enemy.h"
#include "Equipment.h"
#include "ConsumableItem.h"
#include "TiledVector.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"

template<class T>
EnemysItem<T>::EnemysItem(std::unique_ptr<T> contents, TiledVector tilePos)
    : TiledObject(tilePos)
    , _contents(std::move(contents))
    , _countAfterEmpty(0)
{
    _type = TiledObject::Type::ITEM;

    if (typeid(T) == typeid(Equipment))
    {
        _graph.Load("graph/item/treasure01.png");
        _openedImage = IMAGE_RESOURCE_TABLE->Create("graph/background/treasure05.png");
    }
    else if (typeid(T) == typeid(ConsumableItem))
    {
        _graph.Load("graph/item/treasureB01.png");
        _openedImage = IMAGE_RESOURCE_TABLE->Create("graph/item/treasure05.png");
    }

    _contentsGraph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
    _contentsGraph.SetResource(_contents->_image);
    _contentsGraph.SetPriority(5);
    _contentsGraph.SetDisplayMode(false);

    _openSound.Load("sound/openTreasure.wav");
    _openSound.SetVolume(225);
}


template<class T>
EnemysItem<T>::~EnemysItem()
{
}


static void LoadItem(std::string itemData, int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects)
{
    if (itemData.find("&book") != std::string::npos)
    {
        std::string fileName = "book.png";
        std::unique_ptr<Equipment> contents = std::make_unique<Equipment>(BattleParameter(0, 0, 0, 10, 10, 0), 100, fileName);
        objects.push_back(std::make_shared<EnemysItem<Equipment>>(std::move(contents), TiledVector(countX, countY)));
        return;
    }
    else if (itemData.find("&block") != std::string::npos)
    {
        std::string fileName = "block.png";
        std::unique_ptr<Equipment> contents = std::make_unique<Equipment>(BattleParameter(0, 0, 10, 0, 10, 0), 100, fileName);
        objects.push_back(std::make_shared<EnemysItem<Equipment>>(std::move(contents), TiledVector(countX, countY)));
        return;
    }
    else if (itemData.find("&herb") != std::string::npos)
    {
        std::string fileName = "herb.png";
        auto contents = std::make_unique<ConsumableItem>(100, fileName);
        objects.push_back(std::make_shared<EnemysItem<ConsumableItem>>(std::move(contents), TiledVector(countX, countY)));
        return;
    }
}


template<class T>
void EnemysItem<T>::Update()
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
    else if (_countAfterEmpty == 60)
    {
        _contentsGraph.SetDisplayMode(false);
    }
}


template<class T>
void EnemysItem<T>::Draw()
{
    if (!IsEnable())
        return;

    GraphicalObject::Draw();
}


template<class T>
bool EnemysItem<T>::IsOverwritable(TiledObject* overwriter)
{
    return true;
}


template<class T>
void EnemysItem<T>::GiveItem(Enemy& enemy)
{
    enemy.SetItem(std::move(_contents));
    _contentsGraph.SetDisplayMode(true);
    _graph.SetResource(_openedImage);
    _openSound.Play();
}


template<class T>
bool EnemysItem<T>::IsEnable() const
{
    return (_contents != nullptr);
}