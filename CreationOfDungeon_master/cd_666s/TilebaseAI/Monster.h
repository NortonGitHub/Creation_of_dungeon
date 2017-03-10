#ifndef Monster_h
#define Monster_h

#include "Character.h"
#include "MagicSquare.h"
#include <memory>

class AstarChaser;
class ColleagueNotifyer;
class MagicSquare;

class Monster : public Character
{
public:
    Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName, std::string skillData);
    ~Monster();
    
    void ResetTarget() override;
    void Update() override;
    void DrawParameter(Vector2D anchorPos) override;
    
    bool IsOverwritable(TiledObject* overwriter) override;
    bool IsRunnable();
    
    static void LoadMonsters(std::vector<std::shared_ptr<TiledObject>>& objects, ColleagueNotifyer& notifyer, std::string fileName);
    
    void DrawTargetMarker();
    
//MonsterControllerから呼び出す関数
    void PickMonster() { _hasChoosed = true; };
    void ReleaseMonster() { _hasChoosed = false; };
    void SetTarget(TiledObject *target);
    void SetTarget(TiledVector pos);

//魔法陣から呼び出す関数
    //召喚可能かどうか
    bool IsReadyToProduce();
    //魔法陣への呼び戻し
    void WarpToHome(const MagicSquare& square);

private:

    //名前と効果値からスキル生成
    std::unique_ptr<CharactersSkill> CreateSkillFromName(std::string name, std::string skillData);

    void MoveToNext();

    virtual void OnDie() override;
    
    //意思決定
    virtual void Think() override;
    
    //意思遂行
    virtual void Act() override;
    
    //自分の召喚された陣
    MagicSquare* _home;
    
    std::unique_ptr<AstarChaser> _astar;
    
    //自分がクリック状態かどうか
    bool _hasChoosed;

    //スキル使用後の硬直
    int _countAfterUsingSkill;
};

#endif /* Monster_h */
