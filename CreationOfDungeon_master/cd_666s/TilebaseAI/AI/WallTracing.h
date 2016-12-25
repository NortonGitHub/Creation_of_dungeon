#pragma once
#include "PathFindingAIBase.h"
#include "../TiledVector.h"
#include <vector>

class Character;

class WallTracing : public PathFindingAIBase
{
public:
    WallTracing(Character &owner, std::vector<TiledVector>& pathRef);
    ~WallTracing();
    
    void Reset() override;
    void Update() override;
    void Draw() override;
    
private:

    void Trace();

    TiledVector _direction;
};

