#pragma once
#include "EnemysItem.h"
#include "Enemy.h"
#include "Equipment.h"
#include "ConsumableItem.h"
#include "TiledVector.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"
#include "../Utility/CSVReader.h"

template<class T>
EnemysItem<T>::EnemysItem(std::unique_ptr<T> contents, TiledVector tilePos)
    : TiledObject(tilePos)
    , _contents(std::move(contents))
    , _countAfterEmpty(0)
{
    _type = TiledObject::Type::ITEM;

    if (typeid(T) == typeid(Equipment))
    {
        _graph.Load("resource/graph/item/treasure01.png");
        _openedImage = IMAGE_RESOURCE_TABLE->Create("resource/graph/item/treasure05.png");
    }
    else if (typeid(T) == typeid(ConsumableItem))
    {
        _graph.Load("resource/graph/item/treasureB01.png" );
        _openedImage = IMAGE_RESOURCE_TABLE->Create("resource/graph/item/treasureB05.png");
    }

    _contentsGraph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
    _contentsGraph.SetResource(_contents->_image);
    _contentsGraph.SetPriority(5);
    _contentsGraph.SetDisplayMode(false);

    _openSound.Load("resource/sound/openTreasure.wav");
    _openSound.SetVolume(225);
}


template<class T>
EnemysItem<T>::~EnemysItem()
{
}


static void LoadItem(std::string itemData, int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects)
{

	CSVReader reader;
	std::vector<std::string> ItemArray;

	reader.Read(RESOURCE_TABLE->GetFolderPath() + "csv/StageData/TreasureItem_GoldValue.csv", ItemArray);

    if (itemData.find("&book") != std::string::npos)
    {
        std::string fileName = "book.png";

		int goldValue = -1;
		for (int i = 0; i < ItemArray.size(); i += 2) {
			if (ItemArray[i] == "book") {
				goldValue = std::stoi(ItemArray[i + 1]);
			}
		}

        std::unique_ptr<Equipment> contents = std::make_unique<Equipment>("book", BattleParameter(0, 0, 0, 20, 0, 0), goldValue, fileName);
        objects.push_back(std::make_shared<EnemysItem<Equipment>>(std::move(contents), TiledVector(countX, countY)));
        return;
    }
    else if (itemData.find("&block") != std::string::npos)
    {
        std::string fileName = "block.png";

		int goldValue = -1;
		for (int i = 0; i < ItemArray.size(); i += 2) {
			if (ItemArray[i] == "block") {
				goldValue = std::stoi(ItemArray[i + 1]);
			}
		}

        std::unique_ptr<Equipment> contents = std::make_unique<Equipment>("block", BattleParameter(0, 0, 20, 0, 0, 0), goldValue, fileName);
        objects.push_back(std::make_shared<EnemysItem<Equipment>>(std::move(contents), TiledVector(countX, countY)));
        return;
    }
    else if (itemData.find("&herb") != std::string::npos)
    {
        std::string fileName = "herb.png";

		int goldValue = -1;
		for (int i = 0; i < ItemArray.size(); i += 2) {
			if (ItemArray[i] == "herb") {
				goldValue = std::stoi(ItemArray[i + 1]);
			}
		}

        auto contents = std::make_unique<ConsumableItem>("herb", goldValue, fileName);
        objects.push_back(std::make_shared<EnemysItem<ConsumableItem>>(std::move(contents), TiledVector(countX, countY)));
        return;
    }
    else if (itemData.find("&blade") != std::string::npos)
    {
        std::string fileName = "blade.png";

		int goldValue = -1;
		for (int i = 0; i < ItemArray.size(); i += 2) {
			if (ItemArray[i] == "blade") {
				goldValue = std::stoi(ItemArray[i + 1]);
			}
		}

        std::unique_ptr<Equipment> contents = std::make_unique<Equipment>("blade", BattleParameter(0, 20, 0, 0, 0, 0), goldValue, fileName);
        objects.push_back(std::make_shared<EnemysItem<Equipment>>(std::move(contents), TiledVector(countX, countY)));
        return;
    }
    else if (itemData.find("&robe") != std::string::npos)
    {
        std::string fileName = "robe.png";

		int goldValue = -1;
		for (int i = 0; i < ItemArray.size(); i += 2) {
			if (ItemArray[i] == "robe") {
				goldValue = std::stoi(ItemArray[i + 1]);
			}
		}

        std::unique_ptr<Equipment> contents = std::make_unique<Equipment>("robe", BattleParameter(0, 0, 0, 0, 20, 0), goldValue, fileName);
        objects.push_back(std::make_shared<EnemysItem<Equipment>>(std::move(contents), TiledVector(countX, countY)));
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