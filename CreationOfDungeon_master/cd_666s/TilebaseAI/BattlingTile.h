#ifndef BattlingTile_h
#define BattlingTile_h

#include "Character.h"
#include "Enemy.h"
#include "Monster.h"
#include "TiledObject.h"

class BattlingTile : public TiledObject
{
public:
    BattlingTile(std::weak_ptr<Enemy> enemy, std::weak_ptr<Monster> monster, TiledVector tilePos);
    ~BattlingTile();
    
    void Update() override;
    void Draw() override;
    
    //遠距離攻撃
    void AttackFromOutside(int power, int attack, bool isPhysical, TiledObject::Type defenderType);
    //自軍攻撃用ダメージ計算
    void PhysicalAttack(int power, int attack);
    void MagicalAttack(int power, int attack);
    //自軍防御用ダメージ計算
    void PhysicalDamaged(int power, int attack);
    void MagicalDamaged(int power, int attack);

    //void Interact(const Character& atkObj);
    
    //戦闘から離脱
    void RunAway();
    void FinishBattle();

    bool IsOverwritable(TiledObject* overwriter) override;
    
    Enemy* GetEmemy()
    {
        return (_enemy.expired() ? nullptr : _enemy.lock().get());
    }

    Monster* GetMonster()
    {
        return (_monster.expired() ? nullptr : _monster.lock().get());
    }

private:

    //戦闘後判定
    void CheckAlive(const Enemy& enemy, const Monster& monster);
    
    //戦闘タイマー
    int _count;

    bool _attackMonster;

    Sprite _dust2;

    std::weak_ptr<Enemy>_enemy;
    std::weak_ptr<Monster> _monster;
};

#endif /* BattlingTile_h */
