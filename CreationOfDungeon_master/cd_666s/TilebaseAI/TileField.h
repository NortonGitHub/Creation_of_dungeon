#pragma once
#include "../Utility/Singleton.h"
#include "MapTile.h"
#include "AI/Breadcrumb.h"
#include <vector>

class TileField : public Singleton <TileField>
{
    friend class Singleton<TileField>;
    typedef std::vector<std::vector<MapTile*>> Field;
    typedef std::vector<std::vector<int>> StepTable;
    
public:
    TileField();
    ~TileField();
    
    void Init(int width, int height);
    void Draw();
    
    //タイルにおけるオブジェクトを指定のタイルに登録
    void RegistObject(TiledObject &obj, TiledVector pos);
    //タイルにおけるオブジェクトを除外
    void RemoveObject(TiledObject &obj);
    
    //タイルにおけるオブジェクトを指定のタイルに登録
    void RegistBreadcrumb(Breadcrumb *crumb, TiledVector pos);
    //タイルにおけるオブジェクトを除外
    void RemoveBreadcrumb(Breadcrumb *crumb);
    
    
    //除外して登録する処理を一気に行う
    void MoveObject(TiledObject &obj, TiledVector pos);
    
    TiledObject* GetTiledObject(const TiledVector &pos);
    std::vector<TiledObject*> GetTiledObjects(const TiledVector &pos);
    
    const Field &GetFieldRef() const { return _field; }
    
    //フィールドの範囲内にあるかどうか
    const bool IsInside(const TiledVector &pos) const;
    
    //そのマスに移動できるかどうか
    const bool IsMovableThere(TiledVector pos, TiledObject& moveObj) const
    {
        return (     IsInside(pos)
                &&  _field[pos._y][pos._x]->IsRegistable(moveObj));
    }
    
    const Breadcrumb* GetBreadcrumb(TiledVector pos) const
    {
        if (!IsInside(pos))
            return nullptr;
        
        return _field[pos._y][pos._x]->GetBreadcrumb();
    }
    
    const TiledVector GetFieldSize() const { return _fieldSize; }
    
    //AstarやDFSで計算した移動可能マスを表示
    std::vector<TiledVector> GetMovableCell(TiledVector pos, int movableRange);
    std::vector<TiledVector> GetParabolicMovableCell(TiledVector pos, int movableRange, TiledVector::Direction directon);
    
private:
    
    //DFSで自キャラが移動できるマスを計算
    void CalcMovableCell(const TiledVector &pos, StepTable& stepTable, int step, int degree, TiledVector::Direction);
    void CalcParabolicMovableCell(TiledVector pos, const TiledVector &basePos, StepTable& stepTable, int range, TiledVector::Direction dir, TiledVector::Direction baseDir);
    
    
    
    TiledVector _fieldSize;
    Field _field;
    std::vector<GraphicalObject *> _gobjs;
};

#define FIELD TileField::GetInstance()