#ifndef AstarNode_h
#define AstarNode_h

#include "../TiledVector.h"

class AstarNode
{
public:
    AstarNode(TiledVector pos);
    ~AstarNode();
    
    int GetHeuristicCost() const { return _heuristicCost; }
    int GetCost() const { return _cost; }
    int GetScore() { return _score; }
    TiledVector GetChipPos() const { return _pos; }
    AstarNode* GetParentPtr() const { return _parent; }
    
    bool IsReady() const;
    bool IsClosed() const;
    
    void Init();
    void Open(AstarNode *parentNode, AstarNode *aimNode);
    void Close();
    
    const static int MAX_SCORE;
    
private:
    
    enum class STATE
    {
        OPEN,
        NONE,
        CLOSED
    };
    STATE _state;
    
    int _cost;
    int _heuristicCost;
    int _score;
    AstarNode *_parent;
    
    const TiledVector _pos;
};

#endif /* AstarNode_h */
