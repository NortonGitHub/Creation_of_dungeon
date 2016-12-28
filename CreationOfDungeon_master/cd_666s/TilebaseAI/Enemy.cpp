#include "Enemy.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../Resources/ResourceManager.h"
#include "../DebugDraw.h"
#include "StartPoint.h"
#include "Goal.h"
#include "ColleagueNotifyer.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"

#include <array>
#include "../Utility/CSVReader.h"

int Enemy::_defeatedNum = 0;
int Enemy::_enemysNum = 0;

Enemy::Enemy(TiledVector startPos, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer)
: Character(startPos, params, notifyer)
, _baseTarget(baseTarget)
, _searchLength(4)
, _hasAppeared(false)
, _direction(TiledVector::Direction::FORWARD)
, _enterSE(RESOURCE_TABLE->GetFolderPath() + "sound/blockSelect.wav")
{
    _target = &baseTarget;
    
    _astar = new AstarChaser(_target, *this, _pathToTarget, 20, true);

    //自分の味方が経路上にいたら回り込まず継続する
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj)
    {
        return (obj->GetType() == _type);
    }));
    _ai = _astar;
    
    _graph.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/blaver_front.png");
    _left.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/blaver_left.png");
    _right.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/blaver_right.png");
    _back.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/blaver_back.png");

    _graph.GetTexturePtr()->SetRenderType(Texture2D::RenderType::UI);
    _left.GetTexturePtr()->SetRenderType(Texture2D::RenderType::UI);
    _right.GetTexturePtr()->SetRenderType(Texture2D::RenderType::UI);
    _back.GetTexturePtr()->SetRenderType(Texture2D::RenderType::UI);

    _animator.AddAnimation("jumpShot", std::make_shared<GraphArray>("heromove/hero(jump up attack).png"));
    _animator.AddAnimation("punch", std::make_shared<GraphArray>("heromove/hero(punch).png"));
    _animator.AddAnimation("kick", std::make_shared<GraphArray>("heromove/hero(kick).png"));
    _animator.AddAnimation("win", std::make_shared<GraphArray>("heromove/hero_clear.png", 32, 32, 2, 20));

    //開始のアニメーションを指定
    _animator.Switch("normal");
    _graph = *_animator.GetCurrentGraph();

    _position = startPos.GetWorldPos();
    _beforeTilePos = GetTilePos();
    _type = TiledObject::Type::ENEMY;
}


Enemy::~Enemy()
{
    delete _astar;
}


void Enemy::LoadEnemys(std::vector<TiledObject*>& objects, StartPoint* point, Goal* goal, ColleagueNotifyer& notifyer, std::string fileName)
{
    _defeatedNum = 0;
    _enemysNum = 0;

    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(fileName, dataArray, 1);
    
    const int parameterNum = 5;
    std::array<int, parameterNum> params = {0, 0, 0, 0, 0};
    int idx = 0;
    int count = 0;
    for (auto data : dataArray)
    {
        params[count] = std::stoi(data);
        count++;
        
        if (count == parameterNum)
        {
            //戦闘データ設定
            BattleParameter param = {params[0], params[1], params[2], params[3]};
            Enemy* enemy = new Enemy(point->GetTilePos(), param, *goal, notifyer);
            objects.push_back(enemy);
            //出現時間を秒単位に変換して入場者リストに追加
            point->AddToAppearList(enemy, params[4] * 60);
            
            //次のキャラへ
            count = 0;
            idx++;

            _enemysNum++;
        }
    }
}


void Enemy::Init()
{
    _graph.SetDisplayMode(false);
    _back.SetDisplayMode(false);
    _left.SetDisplayMode(false);
    _right.SetDisplayMode(false);

    _graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
    _left.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
    _right.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
    _back.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
}


void Enemy::SwitchAI(PathFindingAIBase* ai)
{
    //現在と同じAIだったら変更なし
    if (_ai == ai)
        return;
    
    _ai->Reset();
    _ai = ai;
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
    if (!_hasAppeared)
        return;
    
    if (_isBattling)
        return;
    
    if (0 < _countAfetrBattle)
    {
        _countAfetrBattle++;
        
        if (_countAfetrBattle < 60)
            return;
        else
            _countAfetrBattle = 0;
    }
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
    TiledVector pos = GetTilePos();
    if (pos != _beforeTilePos)
        _beforeTilePos = pos;
    
    //移動先との差分から向きを更新
    auto dir = (_pathToTarget.size() == 0) ? _target->GetTilePos() - pos : _pathToTarget[0] - pos;
    if (dir == TiledVector::up)
        _direction = TiledVector::Direction::FORWARD;
    else if (dir == TiledVector::down)
        _direction = TiledVector::Direction::BACK;
    else if (dir == TiledVector::left)
        _direction = TiledVector::Direction::LEFT;
    else if (dir == TiledVector::right)
        _direction = TiledVector::Direction::RIGHT;
    
    _beforeTilePos = pos;
    
    //移動が完了してるないなら
    if (0 < _pathToTarget.size())
    {
        //目標へ移動
        MoveToNext();
        return;
    }
    
    //目標の上にいなければ終了
    if (_target->GetTile() != GetTile())
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
    OBJECT_MGR->Add(new BattlingTile(*this, *chara, GetTilePos()));
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


void Enemy::Draw()
{
    _graph.SetDisplayMode(IsEnable() && !_isBattling);
    _left.SetDisplayMode(IsEnable() && !_isBattling);
    _right.SetDisplayMode(IsEnable() && !_isBattling);
    _back.SetDisplayMode(IsEnable() && !_isBattling);

    if (!_hasAppeared || _isBattling)
        return;
    
    switch (_direction)
    {
    case TiledVector::Direction::FORWARD:
        _graph.SetDisplayMode(true);
        _back.SetDisplayMode(false);
        _left.SetDisplayMode(false);
        _right.SetDisplayMode(false);
        break;

    case TiledVector::Direction::LEFT:
        _graph.SetDisplayMode(false);
        _back.SetDisplayMode(false);
        _left.SetDisplayMode(true);
        _right.SetDisplayMode(false);
        break;

    case TiledVector::Direction::RIGHT:
        _graph.SetDisplayMode(false);
        _back.SetDisplayMode(false);
        _left.SetDisplayMode(false);
        _right.SetDisplayMode(true);
        break;

    case TiledVector::Direction::BACK:
        _graph.SetDisplayMode(false);
        _back.SetDisplayMode(true);
        _left.SetDisplayMode(false);
        _right.SetDisplayMode(false);
        break;
    }

    /*
    for (size_t i=0; i<_sight.size(); ++i)
    {
        Debug::DrawRectWithSize(_sight[i].GetWorldPos(), Vector2D(TILE_SIZE, TILE_SIZE),
                                Color4(1.0, 0.5, 0.5, 0.25), true);
    }
    */

    //AIのデバッグ情報
    _ai->Draw();
    
    _graph.SetPosition(_position);
    _back.SetPosition(_position);
    _left.SetPosition(_position);
    _right.SetPosition(_position);

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


void Enemy::OnWin()
{
    Character::OnWin();
    _target = &_baseTarget;
    _astar->SetTarget(_target);
}


void Enemy::Appear()
{
    _hasAppeared = true;
    _enterSE.Play();
}


bool Enemy::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
    
    if (overwriter->GetType() == Type::ENEMY)
        return !_hasAppeared;
    
    return true;
}


bool Enemy::IsEnable() const
{
    return _hasAppeared;
}