#include "BattlingTile.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"
#include "../DebugDraw.h"
#include "BattleCaliculate.h"

BattlingTile::BattlingTile(Enemy& enemy, Monster& monster, TiledVector tilePos)
: TiledObject(tilePos)
, _enemy(enemy)
, _monster(monster)
, _count(0)
, _attackMonster(true)  //魔物から攻撃できる
{
    _graph.Load("resourse/graph/tiledObject/dust1.png");
    _graph.SetPosition(tilePos.GetWorldPos());
    _graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

    _dust2.Load("resourse/graph/tiledObject/dust2.png");
    _dust2.SetPosition(tilePos.GetWorldPos());
    _dust2.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

    //戦闘に介入したキャラは一時的にバトル状態に
    _enemy.OnOccuredBattle(this);
    _monster.OnOccuredBattle(this);
    _position = tilePos.GetWorldPos();
    
    _type = Type::BATTLE;
}


BattlingTile::~BattlingTile()
{
    //戦闘が終わったら両者バトル状態から消える
    _enemy.OnFinishBattle(this);
    _monster.OnFinishBattle(this);
}

//時間経過で戦闘
void BattlingTile::Update()
{
    _count++;
    if (_count < 15)
        return;


    auto monsterParam = _monster.GetAffectedParameter();
    auto enemyParam = _enemy.GetAffectedParameter();

    if (_attackMonster)
    {
        int damage = Battle::GetPhysicalAttackDamage(100, monsterParam._attack, enemyParam._defence);
        _enemy.Damaged(damage);
        _enemy.SetTarget(&_monster);
    }
    else
    {
        int damage = Battle::GetPhysicalDefencedDamage(100, enemyParam._attack, monsterParam._defence);
        _monster.Damaged(damage);
    }

    CheckAlive();

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
    Character* defender = &_enemy;
    auto defenderParam = defender->GetAffectedParameter();
    defender->Damaged(Battle::GetPhysicalAttackDamage(power, attack, defenderParam._defence));
}


void BattlingTile::MagicalAttack(int power, int attack)
{
    Character* defender = &_enemy;
    auto defenderParam = defender->GetAffectedParameter();
    defender->Damaged(Battle::GetMagicalAttackDamage(power, attack, defenderParam._magicDefence));
}


void BattlingTile::PhysicalDamaged(int power, int attack)
{
    Character* defender = &_monster;
    auto defenderParam = defender->GetAffectedParameter();
    defender->Damaged(Battle::GetPhysicalDefencedDamage(power, attack, defenderParam._defence));
}


void BattlingTile::MagicalDamaged(int power, int attack)
{
    Character* defender = &_monster;
    auto defenderParam = defender->GetAffectedParameter();    
    defender->Damaged(Battle::GetMagicalDefencedDamage(power, attack, defenderParam._magicDefence));
}


//勝利したキャラは戦闘マスに立つ
void BattlingTile::Win(Character& chara)
{
}

//敗北したキャラは消える
void BattlingTile::Lose(Character& chara)
{
}

//戦闘から離脱
void BattlingTile::RunAway()
{
    FIELD->RemoveObject(*this);
    OBJECT_MGR->Remove(this);
}

//戦闘後判定
void BattlingTile::CheckAlive()
{
    //生存判定
    if (!_enemy.IsAlive())
    {
        Win(_monster);
        Lose(_enemy);
        FIELD->RemoveObject(*this);
        OBJECT_MGR->Remove(this);
    }
    else if (!_monster.IsAlive())
    {
        Win(_enemy);
        Lose(_monster);
        FIELD->RemoveObject(*this);
        OBJECT_MGR->Remove(this);
    }
}

//上書き不可
bool BattlingTile::IsOverwritable(TiledObject* overwriter)
{
    return false;
}