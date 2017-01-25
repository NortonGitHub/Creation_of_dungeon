#ifndef TiledObjectMnager_h
#define TiledObjectMnager_h

#include "../Utility/Singleton.h"
#include "../Utility/PoolingSystem.h"
#include "TiledObject.h"

class TiledObjectManager : public Singleton<TiledObjectManager>
{
    friend class Dungeon;
public:
    TiledObjectManager();
    ~TiledObjectManager();
    
    void Add(std::shared_ptr<TiledObject> obj);
    //void Remove(std::weak_ptr<TiledObject> obj);
    void Remove(const TiledObject* obj);
    
    void Clear();
    void Refresh();
    
    //タイルが点を含んでいるオブジェクトを取得
    std::vector<TiledObject*> GetContainedObjects(Vector2D vec);
    
private:
    
    std::vector<std::shared_ptr<TiledObject>> _objects;

    bool _needRefresh;
    std::vector<const TiledObject*> _deleteOrders;
    std::vector<std::shared_ptr<TiledObject>> _addOrders;
};

#define OBJECT_MGR TiledObjectManager::GetInstance()

#endif /* TiledObjectMnager_h */
