#include "Monster.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"

Monster::Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName)
: Character(startPos, param, notifyer, monsterName)
, _hasChoosed(false)
{
    _target = target;
    _astar = std::make_unique<AstarChaser>(_target, *this, _pathToTarget, 100, true);
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj)
    {
        if (obj->GetType() != Type::ENEMY)
            return false;

        auto enemy = dynamic_cast<Enemy*>(obj);
        return (!enemy->_isBattling); 
    }));

    _ai = _astar.get();

    _type = TiledObject::Type::MONSTER;
    _appearSE.Load("resourse/sound/flame.wav");
    _appearSE.SetVolume(200);
}


Monster::~Monster()
{
}


void Monster::Think()
{
    if (_target != nullptr)
        _ai->Update();
}


void Monster::Update()
{
    Character::Update();

    //魔法陣の上にいるならさらに回復
    auto magicSquare = FIELD->GetTiledObject<MagicSquare>(GetTilePos());
    if (magicSquare != nullptr)
         magicSquare->Interact(*this);
    
    //出現してなければ行動できない
    if (!_hasAppeared)
        return;

    //バトル中なら行動できない
    if (_isBattling)
        return;

    //バトル直後は動けない(連戦防止)
    if (0 < _countAfetrBattle)
    {
        _countAfetrBattle++;

        if (30 < _countAfetrBattle)
            _countAfetrBattle = 0;
    }

    if (CheckActCounter())
    {
        //指示がなければ終了
        if (_ai == nullptr)
            return;
    
        //視界
        _sight = FIELD->GetParabolicMovableCell(GetTilePos(), 5, _direction);
    
        //意思決定
        Think();
    
        //意思遂行
        Act();
    }
    
    auto vec = (GetTilePos() - _beforeTilePos).GetWorldPos() - Vector2D(FIELD_OFFSET_X, FIELD_OFFSET_Y);
    _position += vec * (1.0 / (GetActInterval() + 1));
}


void Monster::Act()
{
    //移動先との差分から向きを更新
    UpdateAttitude();
   
    //次のタイルへ移動
    MoveToNext();
}


void Monster::MoveToNext()
{
    if (_pathToTarget.size() == 0)
        return;

    if (_countAfetrBattle == 0 )
    {
        //敵が正面から来るなら待ち構える
        auto obj = FIELD->GetTiledObject<Enemy>(GetTilePos());
        if (obj != nullptr)
            return;
    }
    
    //移動先を取り出して
    TiledVector pos = GetTilePos();
    pos = _pathToTarget[0];
    
    //キューから削除
    _pathToTarget.erase(_pathToTarget.begin());
    FIELD->MoveObject(*this, pos);
}


void Monster::ResetTarget()
{
    Character::ResetTarget();
    _astar->SetTarget(nullptr);
}


void Monster::DrawTargetMarker()
{
    if (_target != nullptr)
    {
        auto worldPos = _target->GetPosition() + Vector2D(TILE_SIZE / 2, TILE_SIZE / 2);
        Debug::DrawCircle(worldPos,
            TILE_SIZE, ColorPalette::BLACK4, false);

        Debug::DrawLine(worldPos + Vector2D(-TILE_SIZE / 2, 0), worldPos + Vector2D(TILE_SIZE / 2, 0), ColorPalette::BLACK4);
        Debug::DrawLine(worldPos + Vector2D(0, -TILE_SIZE / 2), worldPos + Vector2D(0, TILE_SIZE / 2), ColorPalette::BLACK4);
    }
}

//魔法陣への呼び戻し
void Monster::WarpToHome(const MagicSquare& square)
{
    //バトル中ならバトルから離脱
    if (_isBattling)
    {
        _battle->RunAway();
        ResetCounter();
    }

    OnDie();
}


void Monster::SetTarget(TiledObject *target)
{
    if (!IsEnable() || !IsAlive())
        return;
        
    //目標の初期化
    ResetTarget();
    
    //目標設定
    _target = target;
    _astar->SetTarget(target);
    
    //バトル中ならバトル終了
    if (_isBattling)
    {
        _battle->RunAway();
        ResetCounter();
    }
}


void Monster::SetTarget(TiledVector pos)
{
    if (!IsEnable() || !IsAlive())
        return;
    
    //そこへ移動
    _target = nullptr;
    _astar->SetTarget(pos);
    _astar->FindPath();
    
    //バトル中ならバトル終了
    if (_isBattling)
    {
        _battle->RunAway();
        ResetCounter();
    }
}


void Monster::OnAttacked(Character& attacker)
{
    //攻撃されたら標的を攻撃してきたやつに変更
    Character::OnAttacked(attacker);
    _astar->SetTarget(&attacker);
}


void Monster::OnDie()
{
    //陣に戻る
    auto homePos = _home->GetTilePos();
    _beforeTilePos = homePos;
    _position = homePos.GetWorldPos();
    FIELD->MoveObject(*this, homePos);

    //各パラメータをリセット
    _hasChoosed = false;
    
    //各パラメータをリセット
    ResetCounter();
    ResetTarget();
    _pathToTarget.resize(0);
    _hasAppeared = false;
}


bool Monster::IsRunnable()
{
    auto tilePos = GetTilePos();
    
    if (FIELD->IsMovableThere(tilePos + TiledVector(0, 1), *this))
        return true;
    
    if (FIELD->IsMovableThere(tilePos + TiledVector(0, -1), *this))
        return true;

    if (FIELD->IsMovableThere(tilePos + TiledVector(1, 0), *this))
        return true;

    if (FIELD->IsMovableThere(tilePos + TiledVector(-1, 0), *this))
        return true;
    
    return false;
}

//召喚可能かどうか
bool Monster::IsReadyToProduce() const
{
    //体力が最大 & 召喚されてないなら召喚可能
    return (_battleParameter._maxHP == _battleParameter._hp)
            && (!_hasAppeared);
}

bool Monster::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;

    if (overwriter->GetType() == Type::ENEMY)
        return !_isBattling;

    if (overwriter->GetType() == Type::MONSTER)
        return false;
    
    return true;
}