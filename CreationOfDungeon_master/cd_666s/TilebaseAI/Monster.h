#ifndef Monster_h
#define Monster_h

#include "Character.h"
#include "../../mw_animation/Animator.h"
#include "../Sound/Sound.h"
#include <memory>

class AstarChaser;
class ColleagueNotifyer;
class MagicSquare;

class Monster : public Character
{
public:
    ~Monster();
    
    void Appear();
    void ResetTarget() override;
    
    void Init();
    void Update() override;
    void Draw() override;
    
    bool IsOverwritable(TiledObject* overwriter) override;
    bool IsEnable() const override;
    bool IsRunnable();
    
    static void LoadMonsters(std::vector<TiledObject*>& objects, ColleagueNotifyer& notifyer, std::string fileName);
    
    void DrawTargetMarker();
    void ExitBattle();
    
//MonsterController����Ăяo���֐�
    void PickMonster() { _hasChoosed = true; };
    void ReleaseMonster() { _hasChoosed = false; };
    void SetTarget(TiledObject *target);
    void SetTarget(TiledVector pos);
    
//���@�w����Ăяo���֐�
    //�����\���ǂ���
    bool IsReadyToProduce() const;
    //���@�w�ւ̌Ăі߂�
    void WarpToHome(const MagicSquare& square);

private:

    Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName);

    virtual void OnAttacked(Character& attacker);
    virtual void OnDie() override;
    virtual void OnWin() override;
    
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
    
    //�����������ς݂��ǂ���
    bool _hasAppeared;

    // TODO : �������̉摜��ʓr�p�ӂ����ɍςނ悤�ɂ���
    GraphArray _front, _left, _right, _back;
    Sound _appearSE, _defeatSE;
};

#endif /* Monster_h */
