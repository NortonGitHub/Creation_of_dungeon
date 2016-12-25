#include "AstarNode.h"
#include <math.h>

const int AstarNode::MAX_SCORE = 999;

AstarNode::AstarNode(TiledVector pos)
: _state(STATE::NONE)
, _cost(MAX_SCORE)
, _heuristicCost(MAX_SCORE)
, _score(MAX_SCORE)
, _parent(nullptr)
, _pos(pos)
{
}


void AstarNode::Init()
{
    _state = STATE::NONE;
    _cost = MAX_SCORE;
    _heuristicCost = MAX_SCORE;
    _score = MAX_SCORE;
    _parent = nullptr;
}


void AstarNode::Open(AstarNode *parentNode, AstarNode *aimNode)
{
    //Openできなかったら終了
    if (!IsReady())
        return;
    
    _parent = parentNode;
    
    //実コスト
    _cost = (_parent == nullptr) ? 0 : _parent->_cost + 1;
    
    //推定コスト(タテ + ヨコ)
    _heuristicCost = (aimNode->GetChipPos() - _pos).GetBresenhamLength(false);
    
    //最終的なコスト
    _score = _cost + _heuristicCost;
    
    _state = STATE::OPEN;
}


bool AstarNode::IsReady() const
{
    return (_state == STATE::NONE);
}


bool AstarNode::IsClosed() const
{
    return (_state == STATE::CLOSED);
}


void AstarNode::Close()
{
    _state = STATE::CLOSED;
}


AstarNode::~AstarNode()
{
}