#ifndef TiledObjectMnager_h
#define TiledObjectMnager_h

#include "../Utility/Singleton.h"
#include "../Utility/PoolingSystem.h"
#include "TiledObject.h"
#include <memory>

class TiledObjectManager : public Singleton<TiledObjectManager>
{
    friend class Dungeon;
    friend class MakeDungeon;
	friend class BossBattle;
public:
    TiledObjectManager();
    ~TiledObjectManager();
    
    void Add(std::shared_ptr<TiledObject> obj);
    //void Remove(std::weak_ptr<TiledObject> obj);
    void Remove(const TiledObject* obj);
    
    void Clear();
    void Refresh();

    //特定のオブジェクトを取得
    template<class T>
    T* GetContainedObject(Vector2D vec)
    {
        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //該当タイプがなければ終了
            if (typeid(T) != typeid(*_objects[i]))
                continue;

            //座標をふくんでなければ終了
            if (!_objects[i]->Contain(vec))
                continue;

            //変換可能なら追加
            std::shared_ptr<T> objPtr = std::dynamic_pointer_cast<T>(_objects[i]);
            if (objPtr.get() == nullptr)
                continue;

            return objPtr.get();
        }

        //std::weak_ptr<T> empty;
        return nullptr;
    }

    //特定のオブジェクトを取得
    template<class T>
    std::vector<T*> GetContainedObjects(Vector2D vec)
    {
        std::vector<T*> results;
        results.reserve(16);

        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //該当タイプがなければ終了
            if (typeid(T) != typeid(*_objects[i]))
                continue;

            //タイル内に存在しなければ終了
            if (!_objects[i]->Contain(vec))
                continue;

            //変換可能なら追加
            std::shared_ptr<T> objPtr = std::dynamic_pointer_cast<T>(_objects[i]);
            if (objPtr.get() == nullptr)
                continue;

            results.push_back(objPtr.get());
        }

        return results;
    }

    template<>
    std::vector<TiledObject*> GetContainedObjects(Vector2D vec)
    {
        std::vector<TiledObject*> results;
        results.reserve(16);

        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //タイル内に存在しなければ終了
            if (!_objects[i]->Contain(vec))
                continue;

            results.push_back(_objects[i].get());
        }

        return results;
    }

    //特定のオブジェクトを取得
    template<class T>
    std::shared_ptr<T> GetSharedObject(TiledObject* rawPtr)
    {
        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //該当タイプがなければ終了
            if (typeid(T) != typeid(*_objects[i]))
                continue;

            if (rawPtr == _objects[i].get())
                return std::dynamic_pointer_cast<T>(_objects[i]);
        }

        return nullptr;
    }

    //特定の型のオブジェクトを取得(重いので使用の際に注意)
    template<class T>
    std::shared_ptr<T> GetSharedObject()
    {
        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //該当タイプがなければ終了
            if (typeid(T) != typeid(*_objects[i]))
                continue;

            return std::dynamic_pointer_cast<T>(_objects[i]);
        }

        return nullptr;
    }

    //特定の型のオブジェクトを取得(重いので使用の際に注意)
    template<class T> 
    std::vector<std::shared_ptr<T>> GetSharedObjects()
    {
        std::vector<std::shared_ptr<T>> results;
        results.reserve(16);

        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //該当タイプがなければ終了
            if (typeid(T) != typeid(*_objects[i]))
                continue;

            results.push_back(std::dynamic_pointer_cast<T>(_objects[i]));
        }

        return results;
    }

private:
    
    std::vector<std::shared_ptr<TiledObject>> _objects;
    
private:

    bool _needRefresh;
    std::vector<const TiledObject*> _deleteOrders;
    std::vector<std::shared_ptr<TiledObject>> _addOrders;
};

#define OBJECT_MGR TiledObjectManager::GetInstance()

#endif /* TiledObjectMnager_h */
