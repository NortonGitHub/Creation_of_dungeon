#ifndef Monster_h
#define Monster_h

#include "Character.h"

class PathFindingAIBase;
class WallTracing;
class AstarChaser;
class ColleagueNotifyer;
class MagicSquare;

class Monster : public Character
{
public:
    Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer);
    ~Monster();
    
    void Appear();
    void ResetTarget() override;
    
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
    
    virtual void OnAttacked(Character& attacker);
    virtual void OnDie() override;
    virtual void OnWin() override;
    
    void SwitchAI(PathFindingAIBase* ai);
    void MoveToNext();
    
    //�ӎv����
    virtual void Think() override;
    
    //�ӎv���s
    virtual void Act() override;
    
    //�����̏������ꂽ�w
    MagicSquare* _home;
    
    //���E�̍L��(���^�C����܂ł�)
    int _searchLength;
    
    //AI���W���[���{��
    PathFindingAIBase *_ai;
    
    TiledVector::Direction _direction;
    std::vector<TiledVector> _sight;
    
    WallTracing* _wallTrace;
    AstarChaser* _astar;
    
    //�������N���b�N��Ԃ��ǂ���
    bool _hasChoosed;
    
    //�����������ς݂��ǂ���
    bool _hasAppeared;
};

#endif /* Monster_h */
