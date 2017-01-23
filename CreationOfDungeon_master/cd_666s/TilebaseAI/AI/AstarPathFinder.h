#ifndef AstarPathFinder_h
#define AstarPathFinder_h

#include "AstarNode.h"
#include <vector>
#include <functional>
#include <memory>
#include "../Character.h"

class TiledObject;

class AstarPathFinder
{
public:
    AstarPathFinder(Character& owner, std::vector<TiledVector> &pathRef, bool diagonal);
    ~AstarPathFinder();
    
    void Reset();
    void Draw();
    
    std::vector<TiledVector> GetPathToTarget(TiledVector startPos, TiledVector targetPos, int searchRange);
    
    //ユーザー定義の通行可能な条件式
    void SetAdditionalPassiveFunction(std::function<bool(TiledObject*)> func) { _additionalFunc = std::move(func); };
    
private:
    
    void Search(TiledVector startPos, TiledVector targetPos);
    void CalcAstar(AstarNode *node, AstarNode *parentNode, AstarNode *targetNode);
    void OpenAround(AstarNode *node, AstarNode *aimNode);
    
    //斜め移動を許可するかどうか
    bool _diagonal;
    
    //通行可能な経路の追加条件式
    std::function<bool(TiledObject*)> _additionalFunc;
    
    //自身の経路
    std::vector<TiledVector> &_pathStack;
    
    std::vector<AstarNode *> _openList;
    std::vector<std::vector<std::unique_ptr<AstarNode>>> _nodeTable;
    
    Character& _owner;
};


#endif /* AstarPathFinder_h */
