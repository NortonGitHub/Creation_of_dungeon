#include "PathFindingAIBase.h"


PathFindingAIBase::PathFindingAIBase(Character &owner, std::vector<TiledVector>& pathRef)
: _owner(owner)
, _pathRef(pathRef)
{
}


PathFindingAIBase::~PathFindingAIBase()
{
}


void PathFindingAIBase::Draw()
{
}