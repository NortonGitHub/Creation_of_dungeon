#ifndef EnemysItem_h
#define EnemysItem_h

#include "TiledObject.h"

class EnemysItem : public TiledObject
{
public:
    EnemysItem(TiledVector tilePos);
    ~EnemysItem();
    
    bool IsOverwritable(TiledObject* overwriter) override;
    void Interact(Character& character) override;
    
    void Update() override;
    void Draw() override;
    
    bool IsEnable() const override;
    
private:
    
    bool _isEnable;
    
};

#endif /* EnemysItem_h */
