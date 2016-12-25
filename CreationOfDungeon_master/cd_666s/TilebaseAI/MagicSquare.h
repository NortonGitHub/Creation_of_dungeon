#ifndef MagicSquare_h
#define MagicSquare_h

#include "TiledObject.h"

class Monster;

class MagicSquare : public TiledObject
{
public:
    MagicSquare(TiledVector tilePos, Monster& monster);
    ~MagicSquare();
    
    bool IsOverwritable(TiledObject* overwriter) override;
    void Interact(Character& character) override;
    
    void Update() override;
    void Draw() override;
    
    //自分を召喚した魔法陣かどうか
    bool IsOwner(Monster& monster) { return (&_monster == &monster); }
    
private:
    
    
    //所属している使い魔を召喚する
    void ProduceMonster();
    
    //所属している使い魔を呼び戻す
    void WarpHomeMonster();
    
    Monster& _monster;

    //召喚可能になったときの画像
    Sprite _graph_ready;
};


#endif /* MagicSquare_h */
