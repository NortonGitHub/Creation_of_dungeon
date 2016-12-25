#pragma once
#include "TiledObject.h"
#include "TiledVector.h"

struct BattleParameter;
class ColleagueNotifyer;
class BattlingTile;

class Character : public TiledObject
{
    friend class ColleagueNotifyer;
    
public:
    
    struct BattleParameter
    {
        int _hp;
        int _attack;
        int _defence;
        int _speed;
    };
    
    Character(TiledVector startPos, BattleParameter param, ColleagueNotifyer& notifyer);
    virtual ~Character();
    
    virtual void Update() override;
    virtual void Draw() override;
    
    virtual void Interact(Character& chara) override;
    virtual bool IsOverwritable(TiledObject* overwriter) override;

    virtual void ResetTarget() { _target = nullptr; }
    
    //�o�g���̓��ޏꎞ�̃C�x���g
    void OnOccuredBattle(BattlingTile* battle);
    void OnFinishBattle(BattlingTile* battle);

    bool IsAlive();
    
    //�퓬�p�p�����[�^
    BattleParameter _battleParameter;
    int _maxHP;
    
    bool _isBattling;
    
protected:
    
    TiledVector _beforeTilePos;
    
    //���n��̃L�����Ԃŏ�񋤗L���邽�߂̒ʐM�@
    ColleagueNotifyer& _notifyer;
    
    //AI�s���̊�ƂȂ�L����
    TiledObject *_target;
    
    //AI�ŎZ�o�����p�X
    std::vector<TiledVector> _pathToTarget;
    
    //�����̎Q�����Ă���o�g�����
    BattlingTile* _battle;
    
    int _countAfetrBattle;

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
    
    //�J�E���^���X�V���čs���\���ǂ�����Ԃ�
    bool CheckActCounter();
    void ResetCounter() { _actCounter = 0; }

    //�J�E���^�̐��l�擾
    int GetActCounter() const { return _actCounter; }
    int GetActInterval() const { return _actInterval; }
    
private:
    
    //���̍s���܂ł̃J�E���^
    int _actCounter;
    int _actInterval;
};

