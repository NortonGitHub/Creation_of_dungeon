#pragma once
#include "Character.h"
#include "../Sound/Sound.h"
#include "../../mw_animation/Animator.h"
#include <memory>
#include <string>

class PathFindingAIBase;
class AstarChaser;
class ColleagueNotifyer;
class StartPoint;
class Goal;

class Enemy : public Character
{
public:
    ~Enemy();
    
    void SetTarget(Character *target) { _target = target; };
    
    void Init() override;
    void Update() override;
    void Draw() override;
    
    bool IsOverwritable(TiledObject* overwriter) override;
    bool IsEnable() const override;
    
    void Appear();
    
    static void LoadEnemys(std::vector<TiledObject*>& objects, StartPoint* point, Goal* goal, ColleagueNotifyer& notifyer, std::string fileName);

    static bool HasWipeOuted()
    {
        if (_defeatedNum == 0 || _enemysNum == 0)
            return false;

        return (_enemysNum <= _defeatedNum);
    }

private:
    Enemy(TiledVector, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer, std::string enemyName);
    
    //�ӎv����
    virtual void Think() override;
    
    //�ӎv���s
    virtual void Act() override;
    
    //�v�l�؂�ւ�
    void SwitchAI(PathFindingAIBase* ai);
    
    //�G�Ύ푰�Ɛ퓬
    void Battle(TiledObject* target);
    //�A�C�e���̎擾
    void ObtainItem(TiledObject* target);
    //�S�[���ւ̓��B
    void ArriveAtGoal(TiledObject* target);

    void MoveToNext();
    bool SearchTarget();
    
    virtual void OnAttacked(Character& attacker);
    virtual void OnDie() override;
    virtual void OnWin() override;
    
    //���E�̍L��(���^�C����܂ł�)
    int _searchLength;
    
    //AI�s���̊�ƂȂ�L����
    TiledObject& _baseTarget;
    
    //AI���W���[���{��
    PathFindingAIBase *_ai;
    
    TiledVector::Direction _direction;
    std::vector<TiledVector> _sight;
    
    std::unique_ptr<AstarChaser> _astar;
    
    //�����������ς݂��ǂ���
    bool _hasAppeared;
    
    // TODO : �������̉摜��ʓr�p�ӂ����ɍςނ悤�ɂ���
    GraphArray _front, _left, _right, _back;

    static int _defeatedNum;
    static int _enemysNum;

    Sound _enterSE;
};

