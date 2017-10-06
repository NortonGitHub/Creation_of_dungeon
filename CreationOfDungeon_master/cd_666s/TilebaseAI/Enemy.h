#pragma once
#include "Character.h"
#include "Equipment.h"
#include "EnemysItem.h"
#include "Monster.h"
#include "EnemysSearch.h"
#include "ColleagueNotifyer.h"
#include "FinateTimer.h"
#include "SearchingPriorityNode.h"
#include <memory>
#include <string>

#include "ConsumableItem.h"

class AstarChaser;
class ColleagueNotifyer;
class StartPoint;
class Goal;
class ConsumableItem;

class Enemy : public Character
{
public:
    Enemy(TiledVector, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer, std::string enemyName);
    ~Enemy();
    
    void SetTarget(Character *target);
    void ResetTarget() override;
    
    void Update() override;
    void DrawParameter(Vector2D anchorPos) override;
    
    bool IsOverwritable(TiledObject* overwriter) override;
   
	int GetDefeatedNum() const override { return (_defeatedNum); };

    static void LoadEnemys(std::vector<std::shared_ptr<TiledObject>>& objects, StartPoint& point, Goal& goal, ColleagueNotifyer& notifyer, std::string fileName);

    static bool HasWipeOuted()
    {
        if (_defeatedNum == 0 || _enemysNum == 0)
            return false;

        return (_enemysNum <= _defeatedNum);
    }

    void SetItem(std::unique_ptr<Equipment> itemContents) 
    {
        _equipItem = std::move(itemContents); 
        _equipmentsGraph.SetResource(_equipItem->_image);
        _hasTreasureIcon.SetDisplayMode(true);
    };

    void SetItem(std::unique_ptr<ConsumableItem> itemContents) 
    {
        for (size_t i = 0; i < _consumableItems.size(); ++i)
        {
            if (_consumableItems[i] == nullptr)
            {
                _consumableItems[i] = (std::move(itemContents));
                _consumableItemGraphs[i].SetResource(_consumableItems[i]->_image);
                _hasTreasureIcon.SetDisplayMode(true);
                return;
            }
        }
    };


    void StuckOn(int interval)  { _damageTimer.Reset(interval, true, false); };

private:

    //意思決定
    virtual void Think() override;
    
    //意思遂行
    virtual void Act() override;

    virtual void OnDie() override;

    //敵対種族と戦闘
    void Battle(TiledObject* target);
    //アイテムの取得
    void ObtainItem(TiledObject* target);
    //ゴールへの到達
    void ArriveAtGoal(TiledObject* target);

    void UseItem(BattleParameter& param);
    void MoveToNext();
    
    //ダメージ硬直用タイマー
    FinateTimer _damageTimer;

    //AI行動の基準となる対象
    TiledObject& _baseTarget;

    //装備品
    std::unique_ptr<Equipment> _equipItem;
    //所持品
    std::vector<std::unique_ptr<ConsumableItem>> _consumableItems;

    std::unique_ptr<AstarChaser> _astar;
    
    static int _defeatedNum;
    static int _enemysNum;

    Sprite _equipmentsGraph, _hasTreasureIcon;
    std::vector<Sprite> _consumableItemGraphs;

    std::vector<SearchPriorityNode> _searchRuleList;
    TiledObject* SearhTargetByRuleList();
    void BuildSearchingRuleList();

    template <typename T>
    void SearchTarget(std::vector<TiledObject*>& targets, const TiledVector& tilePos, const SearchPriorityNode::SearchingRange& rangeType) {};
};
