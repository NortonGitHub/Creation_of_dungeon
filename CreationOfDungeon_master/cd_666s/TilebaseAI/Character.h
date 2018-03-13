#pragma once
#include "TiledObject.h"
#include "TiledVector.h"
#include "BattleParameter.h"
#include "ParameterEffecter.h"
#include "CharacterInfomationDisplayer.h"
#include "CharactersSkill.h"
#include "FinateTimer.h"
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

    Character(TiledVector startPos, BattleParameter param, ColleagueNotifyer& notifyer, std::string name, TiledObject::Type type);
    virtual ~Character();

    //意思決定→行動の順序に基づいた操作
    virtual void Action();

    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawParameter(Vector2D anchorPos);
    virtual void ResetTarget();

    virtual bool IsOverwritable(TiledObject* overwriter) override { return false; }    
    virtual bool Contain(Vector2D pos) const override;

    
    //バトルの入退場時のイベント
    void OnOccuredBattle(BattlingTile* battle);
    void OnFinishBattle(BattlingTile* battle);

    void Appear();
    void Damaged(int damage);
    void AddParameterEffecter(std::unique_ptr<ParameterEffecter> effecter) { _effecters.push_back(std::move(effecter)); };

    bool IsEnable() const override { return _hasAppeared; };
    int GetDefeatedNum() const override { return 0; }
    bool IsAlive() const { return (0 < _battleParameter._hp); }
    bool HasArrived() const override { return _hasArrived; }

    std::string GetName() const { return _name; }
    TiledVector::Direction GetDirection() const { return _direction; }

    BattleParameter GetAffectedParameter();
    BattleParameter GetRawParameter() const override { return _battleParameter; }
    
    void SetDirection(TiledVector::Direction d) { _direction = d; }
	
    bool _isBattling;

	int GetLevel();
	void SetLevel(int lv);

protected:

    void UpdateAttitude();

    //意思決定
    virtual void Think() = 0;
    //意思遂行
    virtual void Act() = 0;

    //倒されたとき
    virtual void OnDie();
    //敵を倒した時
    virtual void OnWin();

    bool CheckActable();

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
    
    FinateTimer _afterBattleTimer;

    //自分が召喚済みかどうか
    bool _hasAppeared;

    bool _hasArrived;

    Animator _animator;

    Sound _appearSE, _defeatSE;

    //次の行動までのカウンタ
    FinateTimer _actCounter;
    
    std::vector<std::unique_ptr<ParameterEffecter>> _effecters;

private:

    //キャラの名前
    std::string _name;

    //戦闘用パラメータ
    BattleParameter _battleParameter;

    CharacterInfomationDisplayer _infoIcon;

    //回復エフェクト用
    Sprite _healGraph;
    GraphArray _healAnimation;

	int Level;

};

