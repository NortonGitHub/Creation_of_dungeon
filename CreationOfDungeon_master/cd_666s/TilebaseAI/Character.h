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
    
    //バトルの入退場時のイベント
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

    //キャラクター固有のスキル
    std::unique_ptr<CharactersSkill> _skill;

    TiledVector _beforeTilePos;
    
    //同系列のキャラ間で情報共有するための通信機
    ColleagueNotifyer& _notifyer;
    
    //AIモジュールの参照
    PathFindingAIBase *_ai;

    //AI行動の基準となるキャラ
    TiledObject *_target;
    
    //AIで算出されるパス
    std::vector<TiledVector> _pathToTarget;

    //姿勢情報
    TiledVector::Direction _direction;

    //視界
    std::vector<TiledVector> _sight;
    
    //自分の参加しているバトル情報
    BattlingTile* _battle;
    
    int _countAfetrBattle;

    //自分が召喚済みかどうか
    bool _hasAppeared;

    Animator _animator;

    Sound _appearSE, _defeatSE;

    void UpdateAttitude();
    
    //意思決定
    virtual void Think() = 0;
    //意思遂行
    virtual void Act() = 0;
        
    //倒されたとき
    virtual void OnDie();
    //敵を倒した時
    virtual void OnWin();
    
    bool CheckActable(const int recoverCountFromAfterBattle);

    //カウンタを更新して行動可能かどうかを返す
    bool CheckActCounter();
    void ResetCounter() { _actCounter = _actInterval; }

    //カウンタの数値取得
    int GetActCounter() const { return _actCounter; }
    int GetActInterval() const { return _actInterval; }
    
    std::vector<std::unique_ptr<ParameterEffecter>> _effecters;

private:

    //次の行動までのカウンタ
    int _actCounter;
    int _actInterval;

    //キャラの名前
    std::string _name;

    //戦闘用パラメータ
    BattleParameter _battleParameter;
};

