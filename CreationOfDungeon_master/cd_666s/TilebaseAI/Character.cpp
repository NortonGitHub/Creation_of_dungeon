#include "Character.h"
#include "TiledObjectMnager.h"
#include "ColleagueNotifyer.h"
#include "TileField.h"
#include "BattlingTile.h"
#include "../DebugDraw.h"

Character::Character(TiledVector startPos, const BattleParameter param, ColleagueNotifyer& notifyer)
: TiledObject(startPos)
, _actCounter(0)
, _actInterval(30)
, _direction(TiledVector::Direction::FORWARD)
, _battleParameter(param)
, _notifyer(notifyer)
, _maxHP(1)
, _countAfetrBattle(0)
, _isBattling(false)
, _target(nullptr)
{
    _notifyer.AddColleague(*this);
    _maxHP = _battleParameter._hp;
    
    _battleParameter._speed = fmin(100, fmax(_battleParameter._speed, 0));
    double speedRatio = static_cast<double>(100 - _battleParameter._speed + 15) / 100;
    _actInterval *= speedRatio;
}


Character::~Character()
{
    _notifyer.RemoveColleague(*this);
}


void Character::Update()
{
    GraphicalObject::Update();
}


void Character::Draw()
{
}


void Character::UpdateAttitude()
{
    TiledVector pos = GetTilePos();

    //移動先との差分から向きを更新
    TiledVector dir;
    if (_pathToTarget.size() == 0)
    {
        if (_target != nullptr)
            dir = _target->GetTilePos() - pos;
    }
    else
    {
        dir = _pathToTarget[0] - pos;
    }

    if (dir == TiledVector::up)
        _direction = TiledVector::Direction::FORWARD;
    else if (dir == TiledVector::down)
        _direction = TiledVector::Direction::BACK;
    else if (dir == TiledVector::left)
        _direction = TiledVector::Direction::LEFT;
    else if (dir == TiledVector::right)
        _direction = TiledVector::Direction::RIGHT;

    _beforeTilePos = pos;
}


void Character::OnOccuredBattle(BattlingTile* battle)
{
    _beforeTilePos = GetTilePos();
    _position = GetTilePos().GetWorldPos();
    _battle = battle;
    _isBattling = true;
    _pathToTarget.clear();
    _pathToTarget.resize(0);
}


void Character::OnFinishBattle(BattlingTile* battle)
{
    if (battle == _battle)
        _battle = nullptr;

    _isBattling = false;
    _countAfetrBattle = 1;
}


bool Character::IsOverwritable(TiledObject* overwriter)
{
    return false;
}


bool Character::CheckActCounter()
{
    if (_actCounter <  _actInterval)
    {
        _actCounter++;
        return false;
    }
    
    _actCounter = 0;
    return true;
}


void Character::Interact(Character& chara)
{
    //敵が隣にいれば戦闘
    chara.Attack(*this);
    
    OnAttacked(chara);
    
    //戦闘で倒されたかを確認して
    if (!IsAlive())
    {
        OnDie();
        
        //情報共有網からも除外
        chara._notifyer.NotifyRemoveTarget(*this);
        chara.ResetTarget();
        chara.OnWin();
    }
}


void Character::Attack(Character &defender)
{
    BattleParameter& defenderParameter = defender._battleParameter;
    
    //ダメージの計算式 : こちらの攻撃力 - 相手の防御力
    int damage = _battleParameter._attack - defenderParameter._defence;
    //ダメージは0以上
    damage = fmax(damage, 0);
    
    defenderParameter._hp -= damage;
}


void Character::OnAttacked(Character& attacker)
{
    //相手は攻撃元に気づく
    _target = &attacker;
}


void Character::OnDie()
{    
    //フィールドから除外
    OBJECT_MGR->Remove(this);
}


void Character::OnWin()
{
}


bool Character::IsAlive()
{
    return (0 < _battleParameter._hp);
}