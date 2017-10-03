#include "Monster.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "ColleagueNotifyer.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"
#include "../DebugDraw.h"
#include "../InputManager/InputManager.h"

Monster::Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName, std::string skillData)
: Character(startPos, param, notifyer, monsterName, TiledObject::Type::MONSTER)
, _hasChoosed(false)
, _countAfterUsingSkill(30)
{
    _target = target;
    _astar = std::make_unique<AstarChaser>(_target, *this, _pathToTarget, 100, true);
    /*
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj)
    {
        if (obj->GetType() != Type::ENEMY)
            return false;

        auto enemy = dynamic_cast<Enemy*>(obj);
        return (!enemy->_isBattling); 
    }));
    */

    _skill = CreateSkillFromName(monsterName, skillData);
    _ai = _astar.get();

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
    
    //行動可能かチェック
    if (!CheckActable())
        return;

    if (_skill.get() != nullptr
        && _skill->IsReadyToUse()
        && MOUSE->DoubleClicked()
        && Contain(MOUSE->GetCursorPos()))
    {
        _skill->Activate();
    }

    if (_skill.get() != nullptr
        && _countAfterUsingSkill < 30)
    {
        _countAfterUsingSkill++;
        return;
    }

    Character::Action();
}


void Monster::Act()
{
    //移動先との差分から向きを更新
    //UpdateAttitude();
   
    //次のタイルへ移動
    MoveToNext();
}


void Monster::MoveToNext()
{
    if (_pathToTarget.size() == 0)
        return;

    /*
    if (!_afterBattleTimer.IsCounting())
    {
        //敵が正面から来るなら待ち構える
        auto obj = FIELD->GetTiledObject<Enemy>(GetTilePos());
        if (obj != nullptr)
            return;
    }
    */
    
    //移動先を取り出して
    TiledVector pos = _pathToTarget[0];
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
        Debug::DrawCircle(worldPos, TILE_SIZE, ColorPalette::BLACK4, false);
        Debug::DrawLine(worldPos + Vector2D(-TILE_SIZE / 2, 0), worldPos + Vector2D(TILE_SIZE / 2, 0), ColorPalette::BLACK4);
        Debug::DrawLine(worldPos + Vector2D(0, -TILE_SIZE / 2), worldPos + Vector2D(0, TILE_SIZE / 2), ColorPalette::BLACK4);
    }
}

//魔法陣への呼び戻し
void Monster::WarpToHome(const MagicSquare& square)
{
    //バトル中ならバトルから離脱
    if (_isBattling)
        _battle->RunAway();
//        ResetCounter();

    OnDie();
}


void Monster::SetTarget(TiledObject *target)
{
    if (!IsEnable() || !IsAlive() || _isBattling)
        return;
        
    //目標の初期化
    ResetTarget();
    
    //目標設定
    _target = target;
    _astar->SetTarget(target);
}


void Monster::SetTarget(TiledVector pos)
{
    if (!IsEnable() || !IsAlive() || _isBattling)
        return;
    
    //そこへ移動
    _target = nullptr;
    _astar->SetTarget(pos);
    _astar->FindPath();
}


void Monster::OnDie()
{
    Character::OnDie();

    //陣に戻る
    auto homePos = _home->GetTilePos();
    _beforeTilePos = homePos;
    _position = homePos.GetWorldPos();
    FIELD->MoveObject(*this, homePos);

    //各パラメータをリセット
    ResetTarget();
    _hasChoosed = false;
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
bool Monster::IsReadyToProduce()
{
    auto param = GetAffectedParameter();
    //体力が最大 & 召喚されてないなら召喚可能
    return (param._maxHP == param._hp)
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