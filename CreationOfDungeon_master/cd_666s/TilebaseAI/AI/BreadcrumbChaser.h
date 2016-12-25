#pragma once
#include "PathFindingAIBase.h"
#include "../TiledVector.h"
#include <vector>

class Character;

class BreadcrumbChaser : public PathFindingAIBase
{
public:
    BreadcrumbChaser(std::vector<TiledVector> &pathRef, Character &owner, int searchRange, bool diagonal);
    ~BreadcrumbChaser();
    
    void Update() override;
    void Reset() override;
    
private:
    
    void SearchBreadcrumbs();
    
    //’Tõ‚·‚éüˆÍƒ}ƒX‚Ì”ÍˆÍ
    int _searchRange;
    
    int _currentID;
    
    bool _diagonal;    
};

