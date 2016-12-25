#pragma once
#include "../TiledVector.h"
#include <vector>

class Character;

class PathFindingAIBase
{
public:
    PathFindingAIBase(Character &owner, std::vector<TiledVector>& pathRef);
    virtual ~PathFindingAIBase();

    virtual void Reset() = 0;
    virtual void Update() = 0;
    virtual void Draw();
    
protected:
    
    //思考をする本体
    Character &_owner;
    
    //自身の経路
    std::vector<TiledVector> &_pathRef;
};

