#ifndef AstarChaser_h
#define AstarChaser_h

#include "PathFindingAIBase.h"
#include "../TiledVector.h"
#include "AstarNode.h"
#include "AstarPathFinder.h"
#include <vector>

class Character;
class TiledObject;

class AstarChaser : public PathFindingAIBase
{
public:
    AstarChaser(TiledObject* target, Character &owner, std::vector<TiledVector>& pathRef, int searchRange, bool diagonal);
    ~AstarChaser();
    
    void Update() override;
    void Draw() override;
    void Reset() override;

    void FindPath();

    void SetSearchRange(int searchRange) { _searchRange = searchRange; }
    void SetTarget(TiledObject* target);
    void SetTarget(TiledVector targetPos);
    void SetAdditionalFunc(std::function<bool(TiledObject*)> func){ _aster.SetAdditionalPassiveFunction(func); }
    
private:
    
    //í«ê’ëŒè€
    TiledObject*_target;
    TiledVector _targetPos;
    
    AstarPathFinder _aster;
    int _searchRange;
};

#endif /* AstarChaser_h */
