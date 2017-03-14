#pragma once
#include "TiledObject.h"
#include "TiledVector.h"
#include "BattleParameter.h"
#include "ParameterEffecter.h"
#include "CharactersSkill.h"
#include "AI/PathFindingAIBase.h"

#include "../Sound/Sound.h"
#include "../../mw_animation/Animator.h"

class ColleagueNotifyer;
class BattlingTile;

class Character : public TiledObject
{
    friend class ColleagueNotifyer;
    friend class MagicSquare;
    
public:

    Character(TiledVector startPos, BattleParameter param, ColleagueNotifyer& notifyer, std::string name);
    virtual ~Character();
    
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawParameter(Vector2D anchorPos);

    virtual bool IsOverwritable(TiledObject* overwriter) override;
    virtual bool Contain(Vector2D pos) const override;

    virtual void ResetTarget() 
    {
        _target = nullptr; 
        _pathToTarget.clear();
        _pathToTarget.resize(0);
    }
    
    //�o�g���̓��ޏꎞ�̃C�x���g
    void OnOccuredBattle(BattlingTile* battle);
    void OnFinishBattle(BattlingTile* battle);

    void Appear();
    void Damaged(int damage);

    void AddParameterEffecter(std::unique_ptr<ParameterEffecter> effecter) { _effecters.push_back(std::move(effecter)); };
    //void ClearPositiveEffecter();
    //void ClearNegativeEffecter();

    bool IsEnable() const override;
    bool IsAlive() const;

    std::string GetName() const { return _name; }
    TiledVector::Direction GetDirection() const { return _direction; }

    bool _isBattling;

    
    BattleParameter GetAffectedParameter();
	BattleParameter GetRawParameter() const { return _battleParameter; };
    
protected:

    //�L�����N�^�[�ŗL�̃X�L��
    std::unique_ptr<CharactersSkill> _skill;

    TiledVector _beforeTilePos;
    
    //���n��̃L�����Ԃŏ�񋤗L���邽�߂̒ʐM�@
    ColleagueNotifyer& _notifyer;
    
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
    
    //�ӎv����
    virtual void Think() = 0;
    //�ӎv���s
    virtual void Act() = 0;
        
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
    
    std::vector<std::unique_ptr<ParameterEffecter>> _effecters;

private:

    //���̍s���܂ł̃J�E���^
    int _actCounter;
    int _actInterval;

    //�L�����̖��O
    std::string _name;

    //�퓬�p�p�����[�^
    BattleParameter _battleParameter;
};

