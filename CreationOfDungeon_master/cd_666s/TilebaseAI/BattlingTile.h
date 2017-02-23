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
    
    //���R�U���p�_���[�W�v�Z
    void PhysicalAttack(int power, int attack);
    void MagicalAttack(int power, int attack);
    //���R�h��p�_���[�W�v�Z
    void PhysicalDamaged(int power, int attack);
    void MagicalDamaged(int power, int attack);

    //void Interact(const Character& atkObj);
    
    //�퓬���痣�E
    void RunAway();

    bool IsOverwritable(TiledObject* overwriter) override;
    
    Enemy& _enemy;
    Monster& _monster;
    
private:

    //�퓬�㔻��
    void CheckAlive();
    //���������L�����͐퓬�}�X�ɗ���
    void Win(Character& chara);
    //�s�k�����L�����͏�����
    void Lose(Character& chara);
    
    //�퓬�^�C�}�[
    int _count;

    bool _attackMonster;

    Sprite _dust2;
};

namespace Battle
{
    //�����U���p
    double GetPhysicalAttackDamage(int power, int attack, int defence);
    //���@�U���p
    double GetMagicalAttackDamage(int power, int attack, int defence);
    //������_���[�W�p
    double GetPhysicalDefencedDamage(int power, int attack, int defence);
    //���@��_���[�W�p
    double GetMagicalDefencedDamage(int power, int attack, int defence);
};

#endif /* BattlingTile_h */
