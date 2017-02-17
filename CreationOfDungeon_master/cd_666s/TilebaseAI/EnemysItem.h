#ifndef EnemysItem_h
#define EnemysItem_h

#include "Equipment.h"
#include "TiledObject.h"

class Enemy;

class EnemysItem : public TiledObject
{
public:
    EnemysItem(std::unique_ptr<Equipment> contents, TiledVector tilePos);
    ~EnemysItem();
    
    static void LoadItem(std::string itemData, int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects);

    bool IsOverwritable(TiledObject* overwriter) override;
    void Interact(Character& character) override;
    void GiveItem(Enemy& character);
    
    void Update() override;
    void Draw() override;
    
    bool IsEnable() const override;
    
private:
    
    Sprite _contentsGraph;
    std::unique_ptr<Equipment> _contents;

    int _countAfterEmpty;
};

#endif /* EnemysItem_h */
