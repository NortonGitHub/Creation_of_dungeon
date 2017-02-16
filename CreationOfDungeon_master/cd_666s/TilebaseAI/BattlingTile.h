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
    
    //�퓬�Ɋ��ł���͉̂������U���̂�
    void Damaged(int damage, TiledObject::Type type);
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

#endif /* BattlingTile_h */
