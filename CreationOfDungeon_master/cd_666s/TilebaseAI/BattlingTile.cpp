#include "BattlingTile.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "BattleCaliculate.h"
#include "../Resources/ResourceManager.h"


BattlingTile::BattlingTile(std::weak_ptr<Enemy> enemy, std::weak_ptr<Monster> monster, TiledVector tilePos)
: TiledObject(tilePos)
, _enemy(enemy)
, _monster(monster)
, _count(0)
, _attackMonster(true)  //魔物から攻撃できる
{
    _graph.Load("graph/tiledObject/dust1.png");
    _graph.SetPosition(tilePos.GetWorldPos());
    _graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

    _dust2.Load("graph/tiledObject/dust2.png");
    _dust2.SetPosition(tilePos.GetWorldPos());
    _dust2.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

    //戦闘に介入したキャラは一時的にバトル状態に
    _enemy.lock()->OnOccuredBattle(this);
    _monster.lock()->OnOccuredBattle(this);
    _position = tilePos.GetWorldPos();
    
    _type = Type::BATTLE;
}


BattlingTile::~BattlingTile()
{
    //戦闘が終わったら両者バトル状態から消える
    if (!_monster.expired())
    {
        auto monster = _monster.lock();
        monster->OnFinishBattle(this);
        _monster.reset();
    }

    if (!_enemy.expired())
    {
        auto ememy = _enemy.lock();
        ememy->OnFinishBattle(this);
        _enemy.reset();
    }
}

//時間経過で戦闘
void BattlingTile::Update()
{
    _count++;
    if (_count < 15)
        return;

    if (_enemy.expired()
        || _monster.expired())
    {
        FinishBattle();
        return;
    }

    auto monster = _monster.lock();
    auto ememy = _enemy.lock();

    auto monsterParam = monster->GetAffectedParameter();
    auto enemyParam = ememy->GetAffectedParameter();

    if (_attackMonster)
    {
        int damage = Battle::GetPhysicalAttackDamage(100, monsterParam._attack, enemyParam._defence);
        ememy->Damaged(damage);
        ememy->SetTarget(monster.get());
    }
    else
    {
        int damage = Battle::GetPhysicalDefencedDamage(100, enemyParam._attack, monsterParam._defence);
        monster->Damaged(damage);
    }

    CheckAlive(*ememy, *monster);

    _count = 0;
    _attackMonster = !_attackMonster;
}

//戦闘中は砂埃を描画
void BattlingTile::Draw()
{
    if (_attackMonster)
    {
        _graph.SetDisplayMode(false);
        _dust2.SetDisplayMode(true);
    }
    else
    {
        _graph.SetDisplayMode(true);
        _dust2.SetDisplayMode(false);
    }
}


void BattlingTile::AttackFromOutside(int power, int attack, bool isPhysical, TiledObject::Type defenderType)
{
    if (isPhysical)
    {
        (defenderType == Type::ENEMY) ? PhysicalAttack(power, attack) : PhysicalDamaged(power, attack);
    }
    else
    {
        (defenderType == Type::ENEMY) ? MagicalAttack(power, attack) : MagicalDamaged(power, attack);
    }
}


void BattlingTile::PhysicalAttack(int power, int attack)
{
    if (_enemy.expired())
        return;

    auto ememy = _enemy.lock();
    auto defenderParam = ememy->GetAffectedParameter();
    ememy->Damaged(Battle::GetPhysicalAttackDamage(power, attack, defenderParam._defence));
}


void BattlingTile::MagicalAttack(int power, int attack)
{
    if (_enemy.expired())
        return;

    auto ememy = _enemy.lock();
    auto defenderParam = ememy->GetAffectedParameter();
    ememy->Damaged(Battle::GetMagicalAttackDamage(power, attack, defenderParam._magicDefence));
}


void BattlingTile::PhysicalDamaged(int power, int attack)
{
    if (_monster.expired())
        return;

    auto monster = _monster.lock();
    auto defenderParam = monster->GetAffectedParameter();
    monster->Damaged(Battle::GetPhysicalDefencedDamage(power, attack, defenderParam._defence));
}


void BattlingTile::MagicalDamaged(int power, int attack)
{
    if (_monster.expired())
        return;

    auto monster = _monster.lock();
    auto defenderParam = monster->GetAffectedParameter();
    monster->Damaged(Battle::GetMagicalDefencedDamage(power, attack, defenderParam._magicDefence));
}


//戦闘から離脱
void BattlingTile::RunAway()
{
    FinishBattle();
}


void BattlingTile::FinishBattle()
{
    FIELD->RemoveObject(*this);
    OBJECT_MGR->Remove(this);

    //戦闘が終わったら両者バトル状態から消える
    if (!_monster.expired())
    {
        auto monster = _monster.lock();
        monster->OnFinishBattle(this);
        _monster.reset();
    }

    if (!_enemy.expired())
    {
        auto ememy = _enemy.lock();
        ememy->OnFinishBattle(this);
        _enemy.reset();
    }
}

//戦闘後判定
void BattlingTile::CheckAlive(const Enemy& enemy, const Monster& monster)
{
    //生存判定
    if (    !enemy.IsAlive()
        ||  !monster.IsAlive())
    {
        FinishBattle();
        return;
    }
}

//上書き不可
bool BattlingTile::IsOverwritable(TiledObject* overwriter)
{
    return false;
}