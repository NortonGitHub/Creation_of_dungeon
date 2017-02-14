#pragma once
#include "Character.h"
#include "Equipment.h"
#include <memory>
#include <string>

class AstarChaser;
class ColleagueNotifyer;
class StartPoint;
class Goal;

class Enemy : public Character
{
public:
    Enemy(TiledVector, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer, std::string enemyName);
    ~Enemy();
    
    void SetTarget(Character *target) { _target = target; };
    void ResetTarget() override;
    
    void Update() override;
    
    bool IsOverwritable(TiledObject* overwriter) override;
   
    static void LoadEnemys(std::vector<std::shared_ptr<TiledObject>>& objects, StartPoint& point, Goal& goal, ColleagueNotifyer& notifyer, std::string fileName);

    static bool HasWipeOuted()
    {
        if (_defeatedNum == 0 || _enemysNum == 0)
            return false;

        return (_enemysNum <= _defeatedNum);
    }

    void SetItem(std::unique_ptr<Equipment> itemContents) { _attackItem = std::move(itemContents); };

private:
    
    //�ӎv����
    virtual void Think() override;
    
    //�ӎv���s
    virtual void Act() override;

    //�G�Ύ푰�Ɛ퓬
    void Battle(TiledObject* target);
    //�A�C�e���̎擾
    void ObtainItem(TiledObject* target);
    //�S�[���ւ̓��B
    void ArriveAtGoal(TiledObject* target);

    void MoveToNext();
    bool SearchTarget();
    
    virtual void OnAttacked(Character& attacker);
    virtual void OnDie() override;
    
    //AI�s���̊�ƂȂ�L����
    TiledObject& _baseTarget;

    //�����i
    std::unique_ptr<Equipment> _attackItem;// , _defenceItem;

    std::unique_ptr<AstarChaser> _astar;
    
    static int _defeatedNum;
    static int _enemysNum;
};

