#pragma once
#include "../Utility/Singleton.h"
#include "AI/Breadcrumb.h"
#include "MapTile.h"
#include "FieldType.h"
#include <vector>
#include <memory>

class TileField : public Singleton <TileField>
{
    friend class Singleton<TileField>;
    typedef std::vector<std::vector<std::weak_ptr<MapTile>>> Field;
    typedef std::vector<std::vector<int>> StepTable;
    
public:
    TileField();
    ~TileField();
    
    void Clear();
    void Init(int width, int height);
    void Setup();
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
    
    template<class T = TiledObject>
    T* GetTiledObject(const TiledVector &pos)
    {
        //範囲外を参照しようとしたらnullを返す
        if (!IsInside(pos))
            return nullptr;

        return _field[pos._y][pos._x].lock()->GetTiledObject<T>();
    }

    template<class T = TiledObject>
    std::vector<T*> GetTiledObjects(const TiledVector &pos)
    {
        //範囲外を参照しようとしたらnullを返す
        if (!IsInside(pos))
        {
            std::vector<T*> empty;
            return std::move(empty);
        }

        return std::move(_field[pos._y][pos._x].lock()->GetTiledObjects<T>());
    }

    int GetRawNumber(const TiledVector &pos) const;
    void SetRawNumber(const TiledVector &pos, int number);
    FieldType GetFieldType(const TiledVector &pos) const;
    void SetFieldType(const TiledVector &pos, std::string data);

    FieldType GetDefaultFieldType() const { return _defaultFieldType; };
    void SetDefaultFieldType(std::string data);

    const Field &GetFieldRef() const { return _field; }
    
    //フィールドの範囲内にあるかどうか
    const bool IsInside(const TiledVector &pos) const;
    
    //そのマスに移動できるかどうか
    const bool IsMovableThere(TiledVector pos, TiledObject& moveObj) const
    {
        return (     IsInside(pos)
                &&  _field[pos._y][pos._x].lock()->IsRegistable(moveObj));
    }
    
    const Breadcrumb* GetBreadcrumb(TiledVector pos) const
    {
        if (!IsInside(pos))
            return nullptr;
        
        return _field[pos._y][pos._x].lock()->GetBreadcrumb();
    }
    
    const TiledVector GetFieldSize() const { return _fieldSize; }
    
    //AstarやDFSで計算した移動可能マスを表示
    std::vector<TiledVector> GetMovableCell(TiledVector pos, int movableRange);
    std::vector<TiledVector> GetParabolicMovableCell(TiledVector pos, int movableRange, TiledVector::Direction directon);
    
private:
    
    //DFSで自キャラが移動できるマスを計算
    void CalcMovableCell(const TiledVector &pos, StepTable& stepTable, int step, int degree, TiledVector::Direction);
    void CalcParabolicMovableCell(TiledVector pos, const TiledVector &basePos, StepTable& stepTable, int range, TiledVector::Direction dir, TiledVector::Direction baseDir);
    
    FieldType _defaultFieldType;
    TiledVector _fieldSize;
    Field _field;
    std::vector<std::shared_ptr<MapTile>> _gobjs;
};

#define FIELD TileField::GetInstance()