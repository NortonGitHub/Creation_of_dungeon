#ifndef PoolingSystem_h
#define PoolingSystem_h

#include <vector>
#include <memory>
#include "Singleton.h"

/*
 要素をより上位の階層で保持し
 空の要素を自動的に切り詰める配列拡張モジュール
 */

template <class T>
class PoolingSystem
{
public:
    PoolingSystem();
    ~PoolingSystem();
    
    //管理配列に追加
    void Add(std::weak_ptr<T> addOrder);
    //管理配列から除外
    void Remove(std::weak_ptr<T> deleteOrder);

    void Clear();
    void Update();
    
    //配列本体
    std::vector<std::weak_ptr<T>> _objects;
    
protected:
    
    bool _needRefresh;
    void Refresh();
    
    std::vector<std::weak_ptr<T>> _deleteOrders;
    std::vector<std::weak_ptr<T>> _addOrders;
};


#include "PoolingSystem_Private.h"

#endif /* PoolingSystem_h */
