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
    TiledObject* GetTiledObject() const;
    std::vector<TiledObject*> GetTiledObjects() const { return _objects; }
    
private:
    
    //tile
    TiledVector _tilePos;
    
    //そのタイルにあるオブジェクト
    std::vector<TiledObject*> _objects;
    
    //そのタイルにある足跡情報
    Breadcrumb* _breadcrumb;
};

