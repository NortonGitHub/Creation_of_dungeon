#ifndef PoolingSystem_Private_h
#define PoolingSystem_Private_h

#include "PoolingSystem.h"

template <typename T>
PoolingSystem<T>::PoolingSystem(bool autoDelete)
: _needRefresh(false)
, _autoDelete(autoDelete)
{
}


template <typename T>
PoolingSystem<T>::~PoolingSystem()
{
    Clear();
}


template <typename T>
void PoolingSystem<T>::Add(T* addOrder)
{
    if (addOrder != nullptr)
        _addOrders.push_back(addOrder);
}


template <typename T>
void PoolingSystem<T>::Remove(T* deleteOrder)
{
    if (deleteOrder != nullptr)
    {
        _deleteOrders.push_back(deleteOrder);
        _needRefresh = true;
    }
}


template <typename T>
void PoolingSystem<T>::Clear()
{
    if (_autoDelete)
    {
        for (size_t i= 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;
            
            delete _objects[i];
            _objects[i] = nullptr;
        }
    }
    
    _objects.clear();
    _objects.resize(0);
    
    _addOrders.clear();
    _addOrders.resize(0);
    
    _deleteOrders.clear();
    _deleteOrders.resize(0);
}


template <typename T>
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
        if (order == nullptr)
            continue;
        
        for (size_t i= 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;
            
            //削除依頼のものが全リスト中にあったら削除
            if (order != _objects[i])
                continue;
                
            if (_autoDelete)
                delete _objects[i];
            
            _objects[i] = nullptr;
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


template <typename T>
void PoolingSystem<T>::Refresh()
{
    //swap技法用の配列
    std::vector<T *> swaped;
    
    for (auto obj : _objects)
    {
        if (obj == nullptr)
            continue;
        
        //empty以外を追加する
        swaped.push_back(obj);
    }
    
    //切り詰めたリストと入れ替える
    _objects = std::move(swaped);
}

#endif /* PoolingSystem_Private_h */
