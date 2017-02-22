#pragma once
#include "TiledObject.h"
#include "TiledVector.h"
#include "GraphicalObject.h"

class TiledObject;
class Breadcrumb;
class AstarNode;

//class MapTile : public TiledObject
class MapTile : public GraphicalObject
{
public:
    MapTile(int col, int row);
    MapTile(TiledVector pos);
    ~MapTile();
    
    void Init();
    void Draw() override;
    
    static void Regist(TiledObject* obj, std::weak_ptr<MapTile> tile);
    static void Remove(TiledObject* obj, std::weak_ptr<MapTile> tile);
    
    void Regist(Breadcrumb* obj);
    void Remove(Breadcrumb* obj);
    
    bool IsRegistable(TiledObject& obj) const;
    TiledVector GetTilePos() const { return _tilePos; }
    Breadcrumb* GetBreadcrumb() const { return _breadcrumb; }

    template <class T>
    T* GetTiledObject() const
    {
        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //�Y���^�C�v���Ȃ���ΏI��
            if (typeid(T) != typeid(*_objects[i]))
                continue;

            //�ϊ��\�Ȃ�ǉ�
            auto objPtr = dynamic_cast<T*>(_objects[i]);
            if (objPtr == nullptr)
                continue;

            return objPtr;
        }

        //std::weak_ptr<T> empty;
        return nullptr;
    }


    template <class T>
    std::vector<T*> GetTiledObjects() const
    {
        std::vector<T*> results;
        results.reserve(16);

        for (size_t i = 0; i < _objects.size(); ++i)
        {
            if (_objects[i] == nullptr)
                continue;

            //�Y���^�C�v���Ȃ���ΏI��
            if (typeid(T*) != typeid(_objects[i]))
                continue;

            //�ϊ��\�Ȃ�ǉ�
            auto objPtr = dynamic_cast<T*>(_objects[i]);
            if (objPtr == nullptr)
                continue;

            results.push_back(objPtr);
        }

        return results;
    }


    template<>
    TiledObject* GetTiledObject() const
    {
        if (_objects.size() == 0)
            return nullptr;

        return _objects[_objects.size() - 1];
    }


    template<>
    std::vector<TiledObject*> GetTiledObjects() const
    {
        return _objects;
    }

private:
    
    //tile
    TiledVector _tilePos;
    
    //���̃^�C���ɂ���I�u�W�F�N�g
    std::vector<TiledObject*> _objects;
    
    //���̃^�C���ɂ��鑫�Տ��
    Breadcrumb* _breadcrumb;
};
