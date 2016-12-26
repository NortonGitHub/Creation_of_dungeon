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
    
    void Draw() override;
    
    void Regist(TiledObject* obj);
    void Remove(TiledObject* obj);
    
    void Regist(Breadcrumb* obj);
    void Remove(Breadcrumb* obj);
    
    bool IsRegistable(TiledObject& obj) const;
    TiledVector GetTilePos() const { return _tilePos; }
    Breadcrumb* GetBreadcrumb() const { return _breadcrumb; }
    TiledObject* GetTiledObject() const;
    std::vector<TiledObject*> GetTiledObjects() const { return _objects; }
    
private:
    
    //tile
    TiledVector _tilePos;
    
    //���̃^�C���ɂ���I�u�W�F�N�g
    std::vector<TiledObject*> _objects;
    
    //���̃^�C���ɂ��鑫�Տ��
    Breadcrumb* _breadcrumb;
};
