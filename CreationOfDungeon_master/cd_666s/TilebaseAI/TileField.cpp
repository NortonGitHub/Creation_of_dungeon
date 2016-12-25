#include "TileField.h"
#include "TiledObject.h"
#include "GraphicalObject.h"


TileField::TileField()
{
}


TileField::~TileField()
{
}


void TileField::Init(int width, int height)
{
    _fieldSize.Set(width, height);
    _field.resize(height);
    
    for (size_t i = 0; i < _field.size(); i++)
    {
        _field[i].resize(width);
    }
    
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            auto tile = new MapTile(i, j);
            _field[i][j] = tile;
            _gobjs.push_back(tile);
        }
    }
}


void TileField::Draw()
{
    for (auto obj : _gobjs)
        obj->Draw();
}


const bool TileField::IsInside(const TiledVector &pos) const
{
    return !(    pos._x < 0 || _field[0].size() <= pos._x
             ||  pos._y < 0 || _field.size() <= pos._y);
}

//�^�C���ɂ�����I�u�W�F�N�g���w��̃^�C���ɓo�^
void TileField::RegistObject(TiledObject &obj, TiledVector pos)
{
    //�o�^�s�Ȃ�A�o�^���Ȃ�
    if (!IsInside(pos))
        return;
    
    if (!_field[pos._y][pos._x]->IsRegistable(obj))
        return;
    
    _field[pos._y][pos._x]->Regist(&obj);
}


//�^�C���ɂ�����I�u�W�F�N�g�����O
void TileField::RemoveObject(TiledObject &obj)
{
    auto pos = obj.GetTilePos();
    
    //�o�^�s�Ȃ�A�o�^���Ȃ�
    if (!IsInside(pos))
        return;
    
    _field[pos._y][pos._x]->Remove(&obj);
}


//���O���ēo�^���鏈������C�ɍs��
void TileField::MoveObject(TiledObject &obj, TiledVector pos)
{
    //�o�^�s�Ȃ�A�o�^���Ȃ�
    if (!IsInside(pos))
        return;
    
    if (!_field[pos._y][pos._x]->IsRegistable(obj))
        return;
    
    RemoveObject(obj);
    RegistObject(obj, pos);
}


TiledObject* TileField::GetTiledObject(const TiledVector &pos)
{
    //�͈͊O���Q�Ƃ��悤�Ƃ�����null��Ԃ�
    if (!IsInside(pos))
        return nullptr;
    
    return _field[pos._y][pos._x]->GetTiledObject();
}


std::vector<TiledObject*> TileField::GetTiledObjects(const TiledVector &pos)
{
    //�͈͊O���Q�Ƃ��悤�Ƃ�����null��Ԃ�
    if (!IsInside(pos))
    {
        std::vector<TiledObject*> empty;
        return std::move(empty);
    }
    
    return _field[pos._y][pos._x]->GetTiledObjects();
}


//�^�C���ɂ�����I�u�W�F�N�g���w��̃^�C���ɓo�^
void TileField::RegistBreadcrumb(Breadcrumb *crumb, TiledVector pos)
{
    //�o�^�s�Ȃ�A�o�^���Ȃ�
    if (!IsInside(pos))
        return;
    
    _field[pos._y][pos._x]->Regist(crumb);
}


//�^�C���ɂ�����I�u�W�F�N�g�����O
void TileField::RemoveBreadcrumb(Breadcrumb *crumb)
{
    auto pos = crumb->GetTilePos();
    
    //�o�^�s�Ȃ�A�o�^���Ȃ�
    if (!IsInside(pos))
        return;
    
    _field[pos._y][pos._x]->Remove(crumb);
    delete crumb;
}


std::vector<TiledVector> TileField::GetMovableCell(TiledVector pos, int movableRange)
{
    StepTable stepTable(_fieldSize._y);
    for (size_t i = 0; i < stepTable.size(); i++)
        stepTable[i].resize(_fieldSize._x, 0);
    
    //1��𒲂ׂ�(�㉺���E�𒲂ׂ�)
    CalcMovableCell(pos, stepTable, movableRange, 1, TiledVector::Direction::FORWARD);
    CalcMovableCell(pos, stepTable, movableRange, 1, TiledVector::Direction::BACK);
    CalcMovableCell(pos, stepTable, movableRange, 1, TiledVector::Direction::LEFT);
    CalcMovableCell(pos, stepTable, movableRange, 1, TiledVector::Direction::RIGHT);
    
    std::vector<TiledVector> movableTiles;
    
    for (size_t i = 0; i < _fieldSize._y; i++)
    {
        for (size_t j = 0; j < _fieldSize._x; j++)
        {
            if (stepTable[i][j] != 0)
                movableTiles.push_back(TiledVector(j, i));
        }
    }
    
    return movableTiles;
}


void TileField::CalcMovableCell(const TiledVector &pos, StepTable& stepTable, int step, int degree, TiledVector::Direction dir)
{
    //�w������̈ʒu���Z�o
    int x = pos._x;
    int y = pos._y;
    
    if (dir == TiledVector::Direction::LEFT)
        x--;
    else if (dir == TiledVector::Direction::RIGHT)
        x++;
    
    if (dir == TiledVector::Direction::FORWARD)
        y--;
    else if (dir == TiledVector::Direction::BACK)
        y++;
    
    if(!IsInside(TiledVector(x, y)))
        return;
    
    //�w��ʒu��Cell���ړ��\�����ׂ�
    MapTile *cell = _field[y][x];
    TiledObject *obj = cell->GetTiledObject();
    bool isMovable = (obj == nullptr) || (obj != nullptr && obj->GetType() != TiledObject::Type::BLOCK);
    
    //�w��ʒu�̃}�X���ړ��\�Ȃ�
    if (isMovable)
    {
        //���̃}�X�����`�F�b�N(=�����L�^���Ȃ�)��
        //�`�F�b�N�ς݂ł���菭�Ȃ��萔�ňړ��ł���Ȃ�
        if (stepTable[y][x] == 0
            || degree < stepTable[y][x])
        {
            //�萔����
            stepTable[y][x] = degree;
        }
        
        //�ړ��\�ʂ��J�E���g�_�E��
        step--;
        //�J�n�n�_����̋������J�E���g�A�b�v
        degree++;
        
        //�ړ��\�ʂ�0���傫���Ȃ�
        if (0 < step)
        {
            //4aa. ����ɏ㉺���E�𒲂ׂ�
            //���̂Ƃ��A�i��ł��������ɖ߂�Ȃ��悤�ɂ���(���ɒ��ׂĂ��邽��)
            if (dir != TiledVector::Direction::BACK)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::FORWARD);
            if (dir != TiledVector::Direction::FORWARD)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::BACK);
            if (dir != TiledVector::Direction::RIGHT)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::LEFT);
            if (dir != TiledVector::Direction::LEFT)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::RIGHT);
        }
        //�����łȂ��Ȃ�
        else
        {
            //�I��
            return;
        }
    }
    //�����łȂ����
    else
    {
        //�I��
        return;
    }
}


std::vector<TiledVector> TileField::GetParabolicMovableCell(TiledVector pos, int movableRange, TiledVector::Direction directon)
{
    StepTable stepTable(_fieldSize._y);
    for (size_t i = 0; i < stepTable.size(); i++)
        stepTable[i].resize(_fieldSize._x, 0);
    
    //�����ȊO��3������1�}�X��������ׂ�
    if (directon == TiledVector::Direction::LEFT)
    {
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::RIGHT);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::FORWARD);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::BACK);
    }
    else if (directon == TiledVector::Direction::RIGHT)
    {
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::LEFT);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::FORWARD);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::BACK);
    }
    else if (directon == TiledVector::Direction::FORWARD)
    {
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::RIGHT);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::LEFT);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::BACK);
    }
    else if (directon == TiledVector::Direction::BACK)
    {
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::RIGHT);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::FORWARD);
        CalcMovableCell(pos, stepTable, 1, 1, TiledVector::Direction::LEFT);
    }
    
    //���炵�Ă���
    int offset = 2;
    if (directon == TiledVector::Direction::LEFT)
        pos._x += offset;
    else if (directon == TiledVector::Direction::RIGHT)
        pos._x -= offset;
    
    if (directon == TiledVector::Direction::FORWARD)
        pos._y -= offset;
    else if (directon == TiledVector::Direction::BACK)
        pos._y += offset;
    
    //�����̐�𒲂ׂ�
    CalcParabolicMovableCell(pos, pos, stepTable, movableRange + offset, directon, directon);
    
    std::vector<TiledVector> movableTiles;
    
    for (size_t i = 0; i < _fieldSize._y; i++)
    {
        for (size_t j = 0; j < _fieldSize._x; j++)
        {
            if (stepTable[i][j] != 0)
                movableTiles.push_back(TiledVector(j, i));
        }
    }
    
    return movableTiles;
}


void TileField::CalcParabolicMovableCell(TiledVector pos, const TiledVector &basePos, StepTable& stepTable, int range, TiledVector::Direction dir, TiledVector::Direction baseDir)
{
    //�w������̈ʒu���Z�o
    int x = pos._x;
    int y = pos._y;
    
    if (dir == TiledVector::Direction::LEFT)
        x--;
    else if (dir == TiledVector::Direction::RIGHT)
        x++;
    
    if (dir == TiledVector::Direction::FORWARD)
        y++;
    else if (dir == TiledVector::Direction::BACK)
        y--;
    
    if (baseDir != dir)
    {
        if (baseDir == TiledVector::Direction::LEFT)
            x--;
        else if (baseDir == TiledVector::Direction::RIGHT)
            x++;
        
        if (baseDir == TiledVector::Direction::FORWARD)
            y++;
        else if (baseDir == TiledVector::Direction::BACK)
            y--;
    }
    
    pos.Set(x, y);
    
    //�ړ��\������艓����ΏI��
    int degree = (pos - basePos).GetBresenhamLength(true);
    if (range < degree)
        return;
    
    if(!IsInside(TiledVector(x, y)))
        return;
    
    //�w��ʒu��Cell���ړ��\�����ׂ�
    MapTile *cell = _field[y][x];
    TiledObject *obj = cell->GetTiledObject();
    bool isMovable = (obj == nullptr) || (obj != nullptr && obj->GetType() != TiledObject::Type::BLOCK);
    
    //�w��ʒu�̃}�X���ړ��\�Ȃ�
    if (!isMovable)
        return;
    
    //���̃}�X�����`�F�b�N(=�����L�^���Ȃ�)��
    //�`�F�b�N�ς݂ł���菭�Ȃ��萔�ňړ��ł���Ȃ�
    if (stepTable[y][x] == 0
        || degree < stepTable[y][x])
    {
        //�萔����
        stepTable[y][x] = degree;
    }
    
    //4aa. ����ɏ㉺���E�𒲂ׂ�
    //���̂Ƃ��A�i��ł��������ɖ߂�Ȃ��悤�ɂ���(���ɒ��ׂĂ��邽��)
    if (    dir != TiledVector::Direction::BACK
        &&  baseDir != TiledVector::Direction::BACK)
        CalcParabolicMovableCell(pos, basePos, stepTable, range, TiledVector::Direction::FORWARD, baseDir);
    if (    dir != TiledVector::Direction::FORWARD
        &&  baseDir != TiledVector::Direction::FORWARD)
        CalcParabolicMovableCell(pos, basePos, stepTable, range, TiledVector::Direction::BACK, baseDir);
    if (    dir != TiledVector::Direction::RIGHT
        &&  baseDir != TiledVector::Direction::RIGHT)
        CalcParabolicMovableCell(pos, basePos, stepTable, range, TiledVector::Direction::LEFT, baseDir);
    if (    dir != TiledVector::Direction::LEFT
        &&  baseDir != TiledVector::Direction::LEFT)
        CalcParabolicMovableCell(pos, basePos, stepTable, range, TiledVector::Direction::RIGHT, baseDir);
}