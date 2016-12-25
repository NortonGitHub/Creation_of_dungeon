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
    
    void Add(TiledObject* obj);
    void Remove(TiledObject* obj);
    
    void Refresh();
    
    //�^�C�����_���܂�ł���I�u�W�F�N�g���擾
    std::vector<TiledObject*> GetContainedObjects(Vector2D vec);
    
private:
    
    PoolingSystem<TiledObject> _objects;
};

#define OBJECT_MGR TiledObjectManager::GetInstance()

#endif /* TiledObjectMnager_h */
