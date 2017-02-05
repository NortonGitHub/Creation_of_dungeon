#include "Enemy.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"

int Enemy::_defeatedNum = 0;
int Enemy::_enemysNum = 0;

Enemy::Enemy(TiledVector startPos, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer, std::string enemyName)
: Character(startPos, params, notifyer, enemyName)
, _baseTarget(baseTarget)
{
    _target = &baseTarget;
    
    _astar = std::make_unique<AstarChaser>(_target, *this, _pathToTarget, 20, true);
    //自分の味方が経路上にいたら回り込まず継続する
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj)
    {
        if (obj->GetType() != _type)
            return false;

        auto enemy = dynamic_cast<Enemy*>(obj);
        return !enemy->_isBattling;
    }));
    _ai = _astar.get();

    _type = TiledObject::Type::ENEMY;

    _appearSE.Load("resourse/sound/blockSelect.wav");
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

    if (!CheckActable(60))
        return;

    //状態確認フェイズ
    //目標を見失っていたら元の標的へ
    if (_target == nullptr || !_target->IsEnable())
    {
        _target = &_baseTarget;
        _astar->SetTarget(_target);
    }
    
    //戦闘すべきか確認
    if (_countAfetrBattle == 0)
    {
        auto offset = _target->GetPosition() - _position;
        
        if (_target->GetType() == TiledObject::Type::MONSTER
            && offset.GetLength() < TILE_SIZE / 2)
        {
            Battle(_target);
            return;
        }
    }
    
    //行動フェイズ
    if (CheckActCounter())
    {
        //視界更新
        _sight = FIELD->GetParabolicMovableCell(GetTilePos(), 5, _direction);
    
        //意思決定
        Think();
    
        //意思遂行
        Act();
    }

    auto vec = (GetTilePos() - _beforeTilePos).GetWorldPos() - Vector2D(FIELD_OFFSET_X,FIELD_OFFSET_Y);
    _position += vec * (1.0 / (GetActInterval() + 1));
}


void Enemy::Act()
{
    //移動先との差分から向きを更新
    UpdateAttitude();
    
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
            
            if (obj->GetType() != TiledObject::Type::MONSTER
                && obj->GetType() != TiledObject::Type::ITEM)
                continue;
            
            if (!obj->IsEnable())
                continue;
            
            if (!_notifyer.IsChasable(*obj))
                continue;
            
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
    
    //あればアイテム取得
    _target->Interact(*this);
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
    auto chara = dynamic_cast<Monster*>(target);
    OBJECT_MGR->Add(std::make_shared<BattlingTile>(*this, *chara, GetTilePos()));
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


void Enemy::ResetTarget()
{
    Character::ResetTarget();
    _target = &_baseTarget;
    _astar->SetTarget(_target);
}


void Enemy::OnAttacked(Character& attacker)
{
    //攻撃されたら標的を攻撃してきたやつに変更
    Character::OnAttacked(attacker);
    _astar->SetTarget(&attacker);
}


void Enemy::OnDie()
{
    Character::OnDie();
    
    //各パラメータをリセット
    ResetCounter();
    _target = nullptr;
    _hasAppeared = false;
    _defeatedNum++;
}


bool Enemy::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
    
    if (overwriter->GetType() == Type::ENEMY)
        return (!_hasAppeared) && (!_isBattling);
    
    return true;
}