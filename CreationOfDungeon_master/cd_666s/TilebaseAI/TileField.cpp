#include "TileField.h"
#include "TiledObject.h"


TileField::TileField()
{
}


TileField::~TileField()
{
}


void TileField::Clear()
{
    _gobjs.clear();
    _gobjs.resize(0);
    _fieldSize.Set(0, 0);
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
            _gobjs.push_back(std::make_shared<MapTile>(i, j));
            _field[i][j] = _gobjs[_gobjs.size() - 1];
        }
    }
}


void TileField::Setup()
{
    for (auto obj : _gobjs)
        obj->Init();
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

//タイルにおけるオブジェクトを指定のタイルに登録
void TileField::RegistObject(TiledObject &obj, TiledVector pos)
{
    //登録不可なら、登録しない
    if (!IsInside(pos))
        return;
    
    auto tile = _field[pos._y][pos._x].lock();

    if (!tile->IsRegistable(obj))
        return;
    
    MapTile::Regist(&obj, tile);
}


//タイルにおけるオブジェクトを除外
void TileField::RemoveObject(TiledObject &obj)
{
    auto pos = obj.GetTilePos();
    
    //登録不可なら、登録しない
    if (!IsInside(pos))
        return;
    
    auto tile = _field[pos._y][pos._x].lock();
    tile->Remove(&obj, tile);
}


//除外して登録する処理を一気に行う
void TileField::MoveObject(TiledObject &obj, TiledVector pos)
{
    //登録不可なら、登録しない
    if (!IsInside(pos))
        return;
    
    if (!_field[pos._y][pos._x].lock()->IsRegistable(obj))
        return;
    
    RemoveObject(obj);
    RegistObject(obj, pos);
}


int TileField::GetRawNumber(const TiledVector &pos) const
{
    //範囲外を参照しようとしたら-1を返す
    if (!IsInside(pos))
        return -1;

//    return _rawData[pos._y][pos._x];
    return _field[pos._y][pos._x].lock()->_rawNumber;
}


void TileField::SetRawNumber(const TiledVector &pos, int number)
{
    //範囲外を参照しようとしたら-1を返す
    if (!IsInside(pos))
        return;

    _field[pos._y][pos._x].lock()->_rawNumber = number;
}

//タイルにおけるオブジェクトを指定のタイルに登録
void TileField::RegistBreadcrumb(Breadcrumb *crumb, TiledVector pos)
{
    //登録不可なら、登録しない
    if (!IsInside(pos))
        return;
    
    _field[pos._y][pos._x].lock()->Regist(crumb);
}


//タイルにおけるオブジェクトを除外
void TileField::RemoveBreadcrumb(Breadcrumb *crumb)
{
    auto pos = crumb->GetTilePos();
    
    //登録不可なら、登録しない
    if (!IsInside(pos))
        return;
    
    _field[pos._y][pos._x].lock()->Remove(crumb);
    delete crumb;
}


std::vector<TiledVector> TileField::GetMovableCell(TiledVector pos, int movableRange)
{
    StepTable stepTable(_fieldSize._y);
    for (size_t i = 0; i < stepTable.size(); i++)
        stepTable[i].resize(_fieldSize._x, 0);
    
    //1つ先を調べる(上下左右を調べる)
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
    //指定方向の位置を算出
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
    
    //指定位置のCellが移動可能か調べる
    std::weak_ptr<MapTile> cell = _field[y][x];
    TiledObject *obj = cell.lock()->GetTiledObject<TiledObject>();
    bool isMovable = (obj == nullptr) || (obj != nullptr && obj->GetType() != TiledObject::Type::BLOCK);
    
    //指定位置のマスが移動可能なら
    if (isMovable)
    {
        //そのマスが未チェック(=歩数記録がない)か
        //チェック済みでもより少ない手数で移動できるなら
        if (stepTable[y][x] == 0
            || degree < stepTable[y][x])
        {
            //手数を代入
            stepTable[y][x] = degree;
        }
        
        //移動可能量をカウントダウン
        step--;
        //開始地点からの距離をカウントアップ
        degree++;
        
        //移動可能量が0より大きいなら
        if (0 < step)
        {
            //4aa. さらに上下左右を調べる
            //このとき、進んできた方向に戻らないようにする(既に調べてあるため)
            if (dir != TiledVector::Direction::BACK)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::FORWARD);
            if (dir != TiledVector::Direction::FORWARD)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::BACK);
            if (dir != TiledVector::Direction::RIGHT)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::LEFT);
            if (dir != TiledVector::Direction::LEFT)
                CalcMovableCell(TiledVector(x, y), stepTable, step, degree, TiledVector::Direction::RIGHT);
        }
        //そうでないなら
        else
        {
            //終了
            return;
        }
    }
    //そうでなければ
    else
    {
        //終了
        return;
    }
}


std::vector<TiledVector> TileField::GetParabolicMovableCell(TiledVector pos, int movableRange, TiledVector::Direction directon)
{
    StepTable stepTable(_fieldSize._y);
    for (size_t i = 0; i < stepTable.size(); i++)
        stepTable[i].resize(_fieldSize._x, 0);
    
    //視線以外の3方向も1マスだけしらべる
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
    
    //ずらしてから
    int offset = 2;
    if (directon == TiledVector::Direction::LEFT)
        pos._x += offset;
    else if (directon == TiledVector::Direction::RIGHT)
        pos._x -= offset;
    
    if (directon == TiledVector::Direction::FORWARD)
        pos._y -= offset;
    else if (directon == TiledVector::Direction::BACK)
        pos._y += offset;
    
    //視線の先を調べる
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
    //指定方向の位置を算出
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
    
    //移動可能距離より遠ければ終了
    int degree = (pos - basePos).GetBresenhamLength(true);
    if (range < degree)
        return;
    
    if(!IsInside(TiledVector(x, y)))
        return;
    
    //指定位置のCellが移動可能か調べる
    std::weak_ptr<MapTile> cell = _field[y][x];
    TiledObject *obj = cell.lock()->GetTiledObject<TiledObject>();
    bool isMovable = (obj == nullptr) || (obj != nullptr && obj->GetType() != TiledObject::Type::BLOCK);
    
    //指定位置のマスが移動可能なら
    if (!isMovable)
        return;
    
    //そのマスが未チェック(=歩数記録がない)か
    //チェック済みでもより少ない手数で移動できるなら
    if (stepTable[y][x] == 0
        || degree < stepTable[y][x])
    {
        //手数を代入
        stepTable[y][x] = degree;
    }
    
    //4aa. さらに上下左右を調べる
    //このとき、進んできた方向に戻らないようにする(既に調べてあるため)
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