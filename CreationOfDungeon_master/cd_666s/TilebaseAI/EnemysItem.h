#ifndef EnemysItem_h
#define EnemysItem_h

#include "TiledObject.h"

class Enemy;

template <class T>
class EnemysItem : public TiledObject
{
public:
    EnemysItem(std::unique_ptr<T> contents, TiledVector tilePos);
    ~EnemysItem();
    
    bool IsOverwritable(TiledObject* overwriter) override;
    void Interact(Character& character) override;
    void GiveItem(Enemy& character);
    
    void Update() override;
    void Draw() override;
    
    bool IsEnable() const override;
    
private:
    
    Sprite _contentsGraph;
    std::unique_ptr<T> _contents;

    int _countAfterEmpty;
};

#include "EnemysItem_Private.h"

#endif /* EnemysItem_h */
