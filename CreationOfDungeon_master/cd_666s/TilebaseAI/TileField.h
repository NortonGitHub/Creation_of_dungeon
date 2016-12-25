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
    
    //�^�C���ɂ�����I�u�W�F�N�g���w��̃^�C���ɓo�^
    void RegistObject(TiledObject &obj, TiledVector pos);
    //�^�C���ɂ�����I�u�W�F�N�g�����O
    void RemoveObject(TiledObject &obj);
    
    //�^�C���ɂ�����I�u�W�F�N�g���w��̃^�C���ɓo�^
    void RegistBreadcrumb(Breadcrumb *crumb, TiledVector pos);
    //�^�C���ɂ�����I�u�W�F�N�g�����O
    void RemoveBreadcrumb(Breadcrumb *crumb);
    
    
    //���O���ēo�^���鏈������C�ɍs��
    void MoveObject(TiledObject &obj, TiledVector pos);
    
    TiledObject* GetTiledObject(const TiledVector &pos);
    std::vector<TiledObject*> GetTiledObjects(const TiledVector &pos);
    
    const Field &GetFieldRef() const { return _field; }
    
    //�t�B�[���h�͈͓̔��ɂ��邩�ǂ���
    const bool IsInside(const TiledVector &pos) const;
    
    //���̃}�X�Ɉړ��ł��邩�ǂ���
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
    
    //Astar��DFS�Ōv�Z�����ړ��\�}�X��\��
    std::vector<TiledVector> GetMovableCell(TiledVector pos, int movableRange);
    std::vector<TiledVector> GetParabolicMovableCell(TiledVector pos, int movableRange, TiledVector::Direction directon);
    
private:
    
    //DFS�Ŏ��L�������ړ��ł���}�X���v�Z
    void CalcMovableCell(const TiledVector &pos, StepTable& stepTable, int step, int degree, TiledVector::Direction);
    void CalcParabolicMovableCell(TiledVector pos, const TiledVector &basePos, StepTable& stepTable, int range, TiledVector::Direction dir, TiledVector::Direction baseDir);
    
    
    
    TiledVector _fieldSize;
    Field _field;
    std::vector<GraphicalObject *> _gobjs;
};

#define FIELD TileField::GetInstance()