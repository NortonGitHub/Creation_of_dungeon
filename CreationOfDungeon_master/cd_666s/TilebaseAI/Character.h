#pragma once
#include "TiledObject.h"
#include "TiledVector.h"
#include "BattleParameter.h"
#include "CharactersSkill.h"
#include "AI/PathFindingAIBase.h"

#include "../Sound/Sound.h"
#include "../../mw_animation/Animator.h"

class ColleagueNotifyer;
class BattlingTile;

class Character : public TiledObject
{
    friend class ColleagueNotifyer;
    
public:

    Character(TiledVector startPos, BattleParameter param, ColleagueNotifyer& notifyer, std::string name);
    virtual ~Character();
    
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawParameter(Vector2D anchorPos);
    
    virtual void Interact(Character& chara) override;
    virtual bool IsOverwritable(TiledObject* overwriter) override;

    virtual void ResetTarget() { _target = nullptr; }
    
    //�o�g���̓��ޏꎞ�̃C�x���g
    void OnOccuredBattle(BattlingTile* battle);
    void OnFinishBattle(BattlingTile* battle);

    void Appear();
    void Damaged(int damage);

    bool IsEnable() const override;
    bool IsAlive();

    std::string GetName() const { return _name; }
    TiledVector::Direction GetDirection() const { return _direction; }

    
    //�퓬�p�p�����[�^
    BattleParameter _battleParameter;
    
    bool _isBattling;
    
protected:

    TiledVector _beforeTilePos;
    
    //���n��̃L�����Ԃŏ�񋤗L���邽�߂̒ʐM�@
    ColleagueNotifyer& _notifyer;
    
    //�L�����N�^�[�ŗL�̃X�L��
    std::unique_ptr<CharactersSkill> _skill;

    //AI���W���[���̎Q��
    PathFindingAIBase *_ai;

    //AI�s���̊�ƂȂ�L����
    TiledObject *_target;
    
    //AI�ŎZ�o�����p�X
    std::vector<TiledVector> _pathToTarget;

    //�p�����
    TiledVector::Direction _direction;

    //���E
    std::vector<TiledVector> _sight;
    
    //�����̎Q�����Ă���o�g�����
    BattlingTile* _battle;
    
    int _countAfetrBattle;

    //�����������ς݂��ǂ���
    bool _hasAppeared;

    Animator _animator;

    Sound _appearSE, _defeatSE;

    void UpdateAttitude();
    void Attack(Character &defender);
    
    //�ӎv����
    virtual void Think() = 0;
    //�ӎv���s
    virtual void Act() = 0;
    
    
    //�U�����ꂽ�Ƃ�
    virtual void OnAttacked(Character& attacker);
    //�|���ꂽ�Ƃ�
    virtual void OnDie();
    //�G��|������
    virtual void OnWin();
    
    bool CheckActable(const int recoverCountFromAfterBattle);

    //�J�E���^���X�V���čs���\���ǂ�����Ԃ�
    bool CheckActCounter();
    void ResetCounter() { _actCounter = _actInterval; }

    //�J�E���^�̐��l�擾
    int GetActCounter() const { return _actCounter; }
    int GetActInterval() const { return _actInterval; }
    
private:

    //���̍s���܂ł̃J�E���^
    int _actCounter;
    int _actInterval;

    //�L�����̖��O
    std::string _name;
};

