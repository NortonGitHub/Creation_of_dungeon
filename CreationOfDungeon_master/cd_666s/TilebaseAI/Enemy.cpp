#include "Enemy.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"
#include "EnemysItem.h"

int Enemy::_defeatedNum = 0;
int Enemy::_enemysNum = 0;

Enemy::Enemy(TiledVector startPos, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer, std::string enemyName)
    : Character(startPos, params, notifyer, enemyName, TiledObject::Type::ENEMY)
    , _baseTarget(baseTarget)
    , _damageTimer(30, false, false)
{
    _target = &baseTarget;
    
    _astar = std::make_unique<AstarChaser>(_target, *this, _pathToTarget, 20, true);
    _ai = _astar.get();

    _appearSE.Load("resourse/sound/blockSelect.wav");
    _hasTreasureIcon.Load("resourse/graph/icon/treasure_attached.png");
    _hasTreasureIcon.SetScale(Vector2D(2.0, 2.0));
    _hasTreasureIcon.SetDisplayMode(false);
    _hasTreasureIcon.SetPriority(Sprite::Priority::UI);

    _consumableItems.resize(3);
    _consumableItemGraphs.resize(3);

    for (size_t i = 0; i<_consumableItemGraphs.size(); ++i)
    {
        _consumableItemGraphs[i].SetPriority(1090);
    }
    _equipmentsGraph.SetPriority(1090);
}


Enemy::~Enemy()
{
}


void Enemy::Think()
{
    bool hasFound = SearchTarget();
    
    //範囲内に入ったら追跡へ
    if (hasFound)
    {
        _astar->SetTarget(_target);
        _astar->SetSearchRange(6);
    }
    //対象が見つからなくても最後に見かけた地点までたどり着いたら
    else
    {
        if (_pathToTarget.size() == 0)
        {
            //ゴールを目指し直す
            _target = &_baseTarget;
            _astar->SetTarget(&_baseTarget);
            _astar->SetSearchRange(20);
        }
    }
    
    _ai->Update();
}


void Enemy::Update()
{
    Character::Update();

    if (_damageTimer.IsCounting())
        _damageTimer.Update();

    if (!CheckActable())
        return;

    //状態確認フェイズ
    //目標を見失っていたら元の標的へ
    if (_target == nullptr || !_target->IsEnable())
    {
        _target = &_baseTarget;
        _astar->SetTarget(_target);
    }
    
    //戦闘すべきか確認
    if (!_afterBattleTimer.IsCounting())
    {
        auto offset = _target->GetPosition() - _position;
        
        if (_target->GetType() == TiledObject::Type::MONSTER
            && offset.GetLength() < TILE_SIZE / 4)
        {
            Battle(_target);
            return;
        }
    }
    
    if (_damageTimer.IsCounting())
        return;


    Character::Action();

    auto graphSize = _hasTreasureIcon.GetSize();
    _hasTreasureIcon.SetPosition(_position + Vector2D(TILE_SIZE - graphSize._x, 0));
}


void Enemy::Act()
{
    if (_skill.get() != nullptr
        //&& _skill->IsReadyToUse()
        && _skill->ShouldActivate())
    {
        _skill->Activate();
        return;
    }

    //移動先との差分から向きを更新
    //UpdateAttitude();
    
    //体力が半分以下でアイテムを所持しているなら回復
    auto param = GetAffectedParameter();
    if (param._hp <= param._maxHP / 2)
        UseItem(param);

    //移動が完了してるないなら
    if (0 < _pathToTarget.size())
    {
        //目標へ移動
        MoveToNext();
        return;
    }
    
    //目標の上にいなければ終了
    if (_target->GetTile().lock() != GetTile().lock())
        return;

     switch(_target->GetType())
     {
     case TiledObject::Type::ITEM:
         ObtainItem(_target);
         return;

     case TiledObject::Type::GOAL:
         ArriveAtGoal(_target);
         return;
     }
}


bool Enemy::SearchTarget()
{
    //対象が決まってないなら視界に入ったものを対象に
    int minOffset = 999;
    bool hasFound = false;
    
    //視界に入ったものを対象にする
    for (size_t i=0; i<_sight.size(); ++i)
    {
        auto objects = FIELD->GetTiledObjects(_sight[i]);
        for (auto obj : objects)
        {
            if (obj == nullptr)
                continue;
            
            if (obj == &_baseTarget)
                continue;
            
            //追跡対象かどうかチェック
            if (obj->GetType() != TiledObject::Type::MONSTER)
            {
                //アイテムが取得可能かチェック
                if (obj->GetType() != TiledObject::Type::ITEM)
                    continue;

                auto objPtr = dynamic_cast<EnemysItem<Equipment>*>(obj);
                if (objPtr != nullptr)
                {
                    if (objPtr->IsEmpty())
                        continue;

                    if (_equipItem != nullptr)
                        continue;
                }
                else
                {
                    auto ptr = dynamic_cast<EnemysItem<ConsumableItem>*>(obj);
                    if (ptr->IsEmpty())
                        continue;

                    bool result = false;
                    for (size_t i = 0; i<_consumableItems.size(); ++i)
                    {
                        if (_consumableItems[i] == nullptr)
                        {
                            result = true;
                            break;
                        }
                    }

                    if (!result)
                        continue;
                }
            }
            
            //対象が無効(存在しないなど)なら無視
            if (!obj->IsEnable())
                continue;
            
            //別の仲間がすでに対象にしているなら無視
            if (!_notifyer.IsChasable(*obj))
                continue;
            
            //ここまで来たら近いほうを優先するようにする
            int offset = (_sight[i] - GetTilePos()).GetBresenhamLength(false);
            if (minOffset <= offset)
                continue;
            
            if (obj->GetType() == TiledObject::Type::MONSTER)
            {
                auto monster = dynamic_cast<Monster*>(obj);
                if (monster->_isBattling)
                    continue;
            }

            minOffset = offset;
            _target = obj;
            hasFound = true;
        }
    }
    
    return hasFound;
}


void Enemy::ObtainItem(TiledObject* target)
{
    //アイテムが隣になければ終了
    auto offset = _target->GetTilePos() - GetTilePos();
    if (offset.GetBresenhamLength(false) > 1)
        return;

    auto equipment = dynamic_cast<EnemysItem<Equipment>*>(target);
    if (equipment != nullptr)
    {
        //あればアイテム取得
        equipment->GiveItem(*this);
    }
    else
    {
        auto item = dynamic_cast<EnemysItem<ConsumableItem>*>(target);
        if (item != nullptr)
        {
            //あればアイテム取得
            item->GiveItem(*this);
        }
        else
        {
            return;
        }
    }

    _notifyer.NotifyRemoveTarget(*_target);

    //元の目標へ
    _target = &_baseTarget;
    _astar->SetTarget(&_baseTarget);
    _astar->SetSearchRange(20);
    
    _ai->Update();
}


void Enemy::ArriveAtGoal(TiledObject* target)
{
    //TODO : ゴールした状態を追加するなどして
    //ゴールしたらターゲッティングされない条件を用意する
    _hasAppeared = false;
    target->Interact(*this);
    OBJECT_MGR->Remove(this);
}


void Enemy::Battle(TiledObject* target)
{
    // TODO : 応急処置として。
    auto enemy = OBJECT_MGR->GetSharedObject<Enemy>(this);
    auto monster = OBJECT_MGR->GetSharedObject<Monster>(target);
    OBJECT_MGR->Add(std::make_shared<BattlingTile>(enemy, monster, GetTilePos()));
}


void Enemy::MoveToNext()
{
    //移動先を取り出して
    TiledVector pos = GetTilePos();
    pos = _pathToTarget[0];
    
    //キューから削除
    _pathToTarget.erase(_pathToTarget.begin());
    
    //目的の経路に移動
    FIELD->MoveObject(*this, pos);
}


void Enemy::UseItem(BattleParameter& param)
{
    for (size_t i = 0; i < _consumableItems.size(); ++i)
    {
        if (_consumableItems[i] != nullptr)
        {
            _consumableItems[i] = nullptr;
            _consumableItemGraphs[i].SetResource(nullptr);
            Damaged(-param._maxHP / 2);
            break;
        }
    }

    //以下、アイテムがあれば終了
    if (_equipItem != nullptr)
        return;

    for (size_t i = 0; i < _consumableItems.size(); ++i)
    {
        if (_consumableItems[i] != nullptr)
            return;
    }

    //ここまで抜けたらアイテムを所持していないのでアイコン消去
    _hasTreasureIcon.SetDisplayMode(false);
}


void Enemy::SetTarget(Character *target) 
{
    if (!IsEnable() || !IsAlive())
        return;

    //目標の初期化
    ResetTarget();

    _target = target; 
    _astar->SetTarget(target); 
}


void Enemy::ResetTarget()
{
    Character::ResetTarget();
    _target = &_baseTarget;
    _astar->SetTarget(_target);
}


void Enemy::OnDie()
{
    Character::OnDie();
    
    //各パラメータをリセット
    _target = nullptr;
    _defeatedNum++;

    //フィールドから除外
    OBJECT_MGR->Remove(this);
}


bool Enemy::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
    
    return true;
}