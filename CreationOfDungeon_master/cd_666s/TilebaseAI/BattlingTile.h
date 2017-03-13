#ifndef BattlingTile_h
#define BattlingTile_h

#include "Character.h"
#include "Enemy.h"
#include "Monster.h"
#include "TiledObject.h"

class BattlingTile : public TiledObject
{
public:
    BattlingTile(Enemy& enemy, Monster& monster, TiledVector tilePos);
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

    bool IsOverwritable(TiledObject* overwriter) override;
    
    Enemy& _enemy;
    Monster& _monster;
    
private:

    //戦闘後判定
    void CheckAlive();
    //勝利したキャラは戦闘マスに立つ
    void Win(Character& chara);
    //敗北したキャラは消える
    void Lose(Character& chara);
    
    //戦闘タイマー
    int _count;

    bool _attackMonster;

    Sprite _dust2;
};

#endif /* BattlingTile_h */
