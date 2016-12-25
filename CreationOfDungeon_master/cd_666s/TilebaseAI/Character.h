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
    
    //バトルの入退場時のイベント
    void OnOccuredBattle(BattlingTile* battle);
    void OnFinishBattle(BattlingTile* battle);

    bool IsAlive();
    
    //戦闘用パラメータ
    BattleParameter _battleParameter;
    int _maxHP;
    
    bool _isBattling;
    
protected:
    
    TiledVector _beforeTilePos;
    
    //同系列のキャラ間で情報共有するための通信機
    ColleagueNotifyer& _notifyer;
    
    //AI行動の基準となるキャラ
    TiledObject *_target;
    
    //AIで算出されるパス
    std::vector<TiledVector> _pathToTarget;
    
    //自分の参加しているバトル情報
    BattlingTile* _battle;
    
    int _countAfetrBattle;

    void Attack(Character &defender);
    
    //意思決定
    virtual void Think() = 0;
    //意思遂行
    virtual void Act() = 0;
    
    
    //攻撃されたとき
    virtual void OnAttacked(Character& attacker);
    //倒されたとき
    virtual void OnDie();
    //敵を倒した時
    virtual void OnWin();
    
    //カウンタを更新して行動可能かどうかを返す
    bool CheckActCounter();
    void ResetCounter() { _actCounter = 0; }

    //カウンタの数値取得
    int GetActCounter() const { return _actCounter; }
    int GetActInterval() const { return _actInterval; }
    
private:
    
    //次の行動までのカウンタ
    int _actCounter;
    int _actInterval;
};

