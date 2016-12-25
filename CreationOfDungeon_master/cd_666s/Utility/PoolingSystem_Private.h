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
    //order���N���A
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
            
            //�폜�˗��̂��̂��S���X�g���ɂ�������폜
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
    
    //��̔z����l�߂�
    if (_needRefresh)
    {
        Refresh();
        _needRefresh = false;
    }
}


template <typename T>
void PoolingSystem<T>::Refresh()
{
    //swap�Z�@�p�̔z��
    std::vector<T *> swaped;
    
    for (auto obj : _objects)
    {
        if (obj == nullptr)
            continue;
        
        //empty�ȊO��ǉ�����
        swaped.push_back(obj);
    }
    
    //�؂�l�߂����X�g�Ɠ���ւ���
    _objects = std::move(swaped);
}

#endif /* PoolingSystem_Private_h */
