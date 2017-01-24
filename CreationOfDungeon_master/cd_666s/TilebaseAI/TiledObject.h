#pragma once
#include "GraphicalObject.h"
#include "TiledVector.h"
#include "../Utility/PoolingSystem.h"

class MapTile;
class Character;

class TiledObject : public GraphicalObject
{
public:
    TiledObject(TiledVector pos);
    virtual ~TiledObject();
    
    enum class Type
    {
        DEFAULT,
        MONSTER,
        ENEMY,
        ITEM,
        BLOCK,
        START,
        GOAL,
        MAGIC_SQUARE,
        BATTLE
    };
    
    //ループ処理の前に1度だけ呼ばれる処理
    virtual void Init();

    //能動動作できるオブジェクトから呼び出される関数
    virtual void Interact(const std::weak_ptr<Character>& character);
    
    //そのオブジェクトの上に別のオブジェクトが乗れるかどうか
    //overwriter : 上に乗ろうとするオブジェクト
    virtual bool IsOverwritable(TiledObject* overwriter) = 0;
    
    virtual void OnClicked();
    
    //アイテム取得での消失や召喚されたかどうかなど、
    //オブジェクトは生成しても判定に用いるかどうかを判断するのに用いる.
    //詳細な条件は派生先によって異なる.
    virtual bool IsEnable() const { return true; }
    
    void SetTile(const std::weak_ptr<MapTile>& tile) { _tile = tile; }
    void ExitTile() { _tile.reset(); }
    
    Type GetType() const { return _type; }
    std::weak_ptr<MapTile> GetTile() { return _tile; }
    TiledVector GetTilePos() const;

protected:
    
    void CheckClicked();
    
    std::string _name;
    Type _type;
    
private:
    std::weak_ptr<MapTile> _tile;
};

