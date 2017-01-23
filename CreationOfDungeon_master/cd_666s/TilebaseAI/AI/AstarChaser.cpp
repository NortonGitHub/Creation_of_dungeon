#include "AstarChaser.h"
#include "../Character.h"
#include "../TileField.h"
#include "../../DebugDraw.h"

AstarChaser::AstarChaser(TiledObject* target
                         , Character &owner
                         , std::vector<TiledVector>& pathRef
                         , int searchRange
                         , bool diagonal)
: PathFindingAIBase(owner, pathRef)
, _target(target)
, _aster(owner, pathRef, diagonal)
, _searchRange(searchRange)
{
}


AstarChaser::~AstarChaser()
{
}


void AstarChaser::Reset()
{
    _pathRef.clear();
    _pathRef.resize(0);
    _target = nullptr;
}


void AstarChaser::Update()
{
    if (_target != nullptr)
        _targetPos = _target->GetTilePos();
    else
        return;

    FindPath();
}


void AstarChaser::FindPath()
{
    _pathRef = _aster.GetPathToTarget(_owner.GetTilePos(), _targetPos, _searchRange);

    if (_pathRef.size() == 0)
        return;

    //ターゲットの一つ前で止まる
    _pathRef.pop_back();
}


void AstarChaser::SetTarget(TiledObject* target)
{
    _target = target;
    
    if (target == nullptr)
        _targetPos = _owner.GetTilePos();
    else
        _targetPos = target->GetTilePos();
}

void AstarChaser::SetTarget(TiledVector targetPos)
{
    _target = nullptr;
    _targetPos = targetPos;
}


void AstarChaser::Draw()
{
    _aster.Draw();
}