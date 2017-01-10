#ifndef Monster_h
#define Monster_h

#include "Character.h"
#include "../../mw_animation/Animator.h"
#include "../Sound/Sound.h"
#include <memory>

class PathFindingAIBase;
class WallTracing;
class AstarChaser;
class ColleagueNotifyer;
class MagicSquare;

class Monster : public Character
{
public:
    Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName);
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
    
//MonsterControllerから呼び出す関数
    void PickMonster() { _hasChoosed = true; };
    void ReleaseMonster() { _hasChoosed = false; };
    void SetTarget(TiledObject *target);
    void SetTarget(TiledVector pos);
    
//魔法陣から呼び出す関数
    //召喚可能かどうか
    bool IsReadyToProduce() const;
    //魔法陣への呼び戻し
    void WarpToHome(const MagicSquare& square);

private:
    
    virtual void OnAttacked(Character& attacker);
    virtual void OnDie() override;
    virtual void OnWin() override;
    
    void SwitchAI(PathFindingAIBase* ai);
    void MoveToNext();
    
    //意思決定
    virtual void Think() override;
    
    //意思遂行
    virtual void Act() override;
    
    //自分の召喚された陣
    MagicSquare* _home;
    
    //視界の広さ(何タイル先までか)
    int _searchLength;
    
    //AIモジュール本体
    PathFindingAIBase *_ai;
    
    TiledVector::Direction _direction;
    std::vector<TiledVector> _sight;
    
    std::unique_ptr<AstarChaser> _astar;
    
    //自分がクリック状態かどうか
    bool _hasChoosed;
    
    //自分が召喚済みかどうか
    bool _hasAppeared;

    // TODO : 複数枚の画像を別途用意せずに済むようにする
    GraphArray _front, _left, _right, _back;
    Sound _appearSE, _defeatSE;
};

#endif /* Monster_h */
