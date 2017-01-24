#ifndef PoolingSystem_Private_h
#define PoolingSystem_Private_h

#include "PoolingSystem.h"

template <class T>
PoolingSystem<T>::PoolingSystem()
: _needRefresh(false)
{
}


template <class T>
PoolingSystem<T>::~PoolingSystem()
{
    Clear();
}


template <class T>
void PoolingSystem<T>::Add(std::weak_ptr<T> addOrder)
{
    if (addOrder.expired())
        return;
    
    _addOrders.push_back(addOrder);
}


template <class T>
void PoolingSystem<T>::Remove(std::weak_ptr<T> deleteOrder)
{
    if (deleteOrder.expired())
        return;
    
    _deleteOrders.push_back(deleteOrder);
    _needRefresh = true;
    
}


template <class T>
void PoolingSystem<T>::Clear()
{
    _objects.clear();
    _objects.resize(0);
    
    _addOrders.clear();
    _addOrders.resize(0);
    
    _deleteOrders.clear();
    _deleteOrders.resize(0);
}


template <class T>
void PoolingSystem<T>::Update()
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
        for (size_t i= 0; i < _objects.size(); ++i)
        {
            if (_objects[i].expired())
                continue;
            
            //削除依頼のものが全リスト中にあったら削除
            auto ptr = _objects[i].lock();
            auto orderPtr = order.lock();
            if (orderPtr != ptr)
                continue;
            
            _objects[i].reset();
            break;
        }
    }

    _deleteOrders.clear();
    _deleteOrders.resize(0);
    
    //空の配列を詰める
    if (_needRefresh)
    {
        Refresh();
        _needRefresh = false;
    }
}


template <class T>
void PoolingSystem<T>::Refresh()
{
    //swap技法用の配列
    std::vector<std::weak_ptr<T>> swaped;
    
    for (auto obj : _objects)
    {
        if (obj.expired())
            continue;

        auto ptr = obj.lock();
        if (ptr == nullptr)
            continue;
        
        //empty以外を追加する
        swaped.push_back(obj);
    }
    
    //切り詰めたリストと入れ替える
    _objects = std::move(swaped);
}

#endif /* PoolingSystem_Private_h */
