#ifndef PoolingSystem_h
#define PoolingSystem_h

#include <vector>
#include "Singleton.h"

template <typename T>
class PoolingSystem
{
public:
    PoolingSystem(bool autoDelete = false);
    ~PoolingSystem();
    
    void Add(T* addOrder);
    void Remove(T* deleteOrder);
    void Clear();
    void Update();
    
    std::vector<T *> _objects;
    
protected:
    
    bool _autoDelete;
    
    bool _needRefresh;
    void Refresh();
    
    std::vector<T *> _deleteOrders;
    std::vector<T *> _addOrders;
};

#include "PoolingSystem_Private.h"

#endif /* PoolingSystem_h */
