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
    
    //意思決定
    virtual void Think() override;
    
    //意思遂行
    virtual void Act() override;
    
    //思考切り替え
    void SwitchAI(PathFindingAIBase* ai);
    
    //敵対種族と戦闘
    void Battle(TiledObject* target);
    //アイテムの取得
    void ObtainItem(TiledObject* target);
    //ゴールへの到達
    void ArriveAtGoal(TiledObject* target);

    void MoveToNext();
    bool SearchTarget();
    
    virtual void OnAttacked(Character& attacker);
    virtual void OnDie() override;
    virtual void OnWin() override;
    
    //視界の広さ(何タイル先までか)
    int _searchLength;
    
    //AI行動の基準となるキャラ
    TiledObject& _baseTarget;
    
    //AIモジュール本体
    PathFindingAIBase *_ai;
    
    TiledVector::Direction _direction;
    std::vector<TiledVector> _sight;
    
    std::unique_ptr<AstarChaser> _astar;
    
    //自分が召喚済みかどうか
    bool _hasAppeared;
    
    // TODO : 複数枚の画像を別途用意せずに済むようにする
    GraphArray _front, _left, _right, _back;

    static int _defeatedNum;
    static int _enemysNum;

    Sound _enterSE;
};

