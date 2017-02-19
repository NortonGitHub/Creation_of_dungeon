#ifndef Monster_h
#define Monster_h

#include "Character.h"
#include "MagicSquare.h"
#include <memory>

class AstarChaser;
class ColleagueNotifyer;
class MagicSquare;

class Monster : public Character
{
public:
    Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName);
    ~Monster();
    
    void ResetTarget() override;
    void Update() override;
    void DrawParameter(Vector2D anchorPos) override;
    
    bool IsOverwritable(TiledObject* overwriter) override;
    bool IsRunnable();
    
    static void LoadMonsters(std::vector<std::shared_ptr<TiledObject>>& objects, ColleagueNotifyer& notifyer, std::string fileName);
    
    void DrawTargetMarker();
    
//MonsterController����Ăяo���֐�
    void PickMonster() { _hasChoosed = true; };
    void ReleaseMonster() { _hasChoosed = false; };
    void SetTarget(TiledObject *target);
    void SetTarget(TiledVector pos);
    
//���@�w����Ăяo���֐�
    //�����\���ǂ���
    bool IsReadyToProduce();
    //���@�w�ւ̌Ăі߂�
    void WarpToHome(const MagicSquare& square);

private:

    virtual void OnAttacked(Character& attacker);
    virtual void OnDie() override;
    
    void MoveToNext();
    
    //�ӎv����
    virtual void Think() override;
    
    //�ӎv���s
    virtual void Act() override;
    
    //�����̏������ꂽ�w
    MagicSquare* _home;
    
    std::unique_ptr<AstarChaser> _astar;
    
    //�������N���b�N��Ԃ��ǂ���
    bool _hasChoosed;
};

#endif /* Monster_h */
