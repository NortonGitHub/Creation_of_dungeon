#pragma once
#include "PathFindingAIBase.h"
#include "../TiledVector.h"
#include <vector>

/*
 基本移動  : 直線移動
 迂回モード: ランダム移動
 */

class Character;
class TiledObject;

class RandomMovement : public PathFindingAIBase
{
public:
    RandomMovement(Character &owner, TiledObject *target, bool diagonal, std::vector<TiledVector> &pathRef);
    ~RandomMovement();
    
    void Reset() override;
    void Update() override;
    
private:
    
    //通常移動
    void MoveToTarget();
    //障害物回避
    void AvoidObstacle();
    
    //障害物により目的地に進めないかをチェック
    bool IsPreventedFrom();
    
    bool _diagonal;
    bool _isAvoiding;
    
    TiledObject* _target;
};

