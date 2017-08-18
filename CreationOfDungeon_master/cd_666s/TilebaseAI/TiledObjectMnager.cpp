#include "TiledObjectMnager.h"


TiledObjectManager::TiledObjectManager()
: _objects(true)
{
}


TiledObjectManager::~TiledObjectManager()
{
    Clear();
}


void TiledObjectManager::Clear()
{
    _objects.clear();
    _objects.resize(0);

    _addOrders.clear();
    _addOrders.resize(0);

    _deleteOrders.clear();
    _deleteOrders.resize(0);
}


void TiledObjectManager::Add(std::shared_ptr<TiledObject> obj)
{
    _addOrders.push_back(obj);
}

/*
void TiledObjectManager::Remove(std::weak_ptr<TiledObject> obj)
{
    if (obj.expired())
        return;

    _deleteOrders.push_back(obj);
    _needRefresh = true;
}
*/


void TiledObjectManager::Remove(const TiledObject* obj)
{
    if (obj == nullptr)
        return;

    _deleteOrders.push_back(obj);
    _needRefresh = true;
}


void TiledObjectManager::Refresh()
{
    for (auto order : _addOrders)
    {
        _objects.push_back(order);
    }
    //orderをクリア
    _addOrders.clear();
    _addOrders.resize(0);

    for (auto order : _deleteOrders)
    {
        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i].get() == nullptr)
                continue;

            //削除依頼のものが全リスト中にあったら削除
            if (order != _objects[i].get())
                continue;

            _objects[i] = nullptr;
            _objects[i].reset();
            _needRefresh = true;
            break;
        }
    }

    _deleteOrders.clear();
    _deleteOrders.resize(0);

    //空の配列を詰める
    if (_needRefresh)
    {
        //swap技法用の配列
        std::vector<std::shared_ptr<TiledObject>> swaped;

        for (auto obj : _objects)
        {
            if (obj == nullptr)
                continue;

            //empty以外を追加する
            swaped.push_back(obj);
        }

        //切り詰めたリストと入れ替える
        _objects = std::move(swaped);
        _needRefresh = false;
    }
}