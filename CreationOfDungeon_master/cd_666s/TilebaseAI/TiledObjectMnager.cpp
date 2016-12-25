#include "TiledObjectMnager.h"


TiledObjectManager::TiledObjectManager()
: _objects(true)
{
}


TiledObjectManager::~TiledObjectManager()
{
    _objects.Clear();
}


void TiledObjectManager::Add(TiledObject* obj)
{
    _objects.Add(obj);
}


void TiledObjectManager::Remove(TiledObject* obj)
{
    _objects.Remove(obj);
}


void TiledObjectManager::Refresh()
{
    _objects.Update();
}


//タイルが点を含んでいるオブジェクトを取得
std::vector<TiledObject*> TiledObjectManager::GetContainedObjects(Vector2D vec)
{
    std::vector<TiledObject*> results;
    results.reserve(16);
    
    std::vector<TiledObject*>& objects = _objects._objects;
    for (size_t i=0; i<objects.size(); ++i)
    {
        if (objects[i]->Contain(vec))
            results.push_back(objects[i]);
    }
    
    return results;
}
