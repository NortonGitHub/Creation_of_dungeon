#include "RandomMovement.h"
#include "../Character.h"
#include "../TileField.h"
#include "../Utility.h"
#include <chrono>
#include <random>


RandomMovement::RandomMovement(Character &owner, TiledObject *target, bool diagonal, std::vector<TiledVector> &pathRef)
: PathFindingAIBase(owner, pathRef)
, _target(target)
, _isAvoiding(false)
, _diagonal(diagonal)
{
}


RandomMovement::~RandomMovement()
{
}


void RandomMovement::Reset()
{
    _isAvoiding = false;
}


void RandomMovement::Update()
{
    //
    if (_isAvoiding)
        AvoidObstacle();
    else
        MoveToTarget();
}


void RandomMovement::MoveToTarget()
{
    //それ以外は単純にLOSで1マス先を見る
    Bresenham(_target->GetTilePos(), _owner.GetTilePos(), _pathRef, _diagonal, 1);
    
    //壁が正面にあったらパターン切り替え
    if (IsPreventedFrom())
    {
        _isAvoiding = true;
        return;
    }
}


void RandomMovement::AvoidObstacle()
{
    //ランダムに値を取り出し、値によって進む方向を変える
    TiledVector move;
    
    //0:上 1:右 2:下 3:左 4:左上 5;右上 6:右下 7:左下
    std::random_device r;
    std::mt19937 value(r());
    
    int patternNum = (_diagonal) ? 8 : 4;
    int randomValue = value() % patternNum;
    
    if (randomValue == 0)
    {
        move.Set(0, -1);
    }
    else if (randomValue == 1)
    {
        move.Set(1, 0);
    }
    else if (randomValue == 2)
    {
        move.Set(0, 1);
    }
    else if (randomValue == 3)
    {
        move.Set(-1, 0);
    }
    else if (randomValue == 4)
    {
        move.Set(-1, -1);
    }
    else if (randomValue == 5)
    {
        move.Set(1, -1);
    }
    else if (randomValue == 6)
    {
        move.Set(1, 1);
    }
    else if (randomValue == 7)
    {
        move.Set(-1, 1);
    }
    
    _pathRef.push_back(_owner.GetTilePos() + move);
    _isAvoiding = false;
}


bool RandomMovement::IsPreventedFrom()
{
    for (auto pathTile : _pathRef)
    {
        //経路上で、どこかで移動できないことがわかったら
        //妨害されたとみなす
        if (!FIELD->IsMovableThere(pathTile, _owner))
            return true;
    }
    
    return false;
}