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

namespace Battle
{
    //物理攻撃用
    double GetPhysicalAttackDamage(int power, int attack, int defence);
    //魔法攻撃用
    double GetMagicalAttackDamage(int power, int attack, int defence);
    //物理被ダメージ用
    double GetPhysicalDefencedDamage(int power, int attack, int defence);
    //魔法被ダメージ用
    double GetMagicalDefencedDamage(int power, int attack, int defence);
};

#endif /* BattlingTile_h */
