#include "MagicBall.h"
#include "TiledObjectMnager.h"
#include "TileField.h"

#include "Character.h"
#include "BattlingTile.h"

#include "../DebugDraw.h"

MagicBall::MagicBall(int power, int attack, int range, double speed, TiledVector startPos, TiledVector::Direction direction, TiledObject::Type type, std::shared_ptr<ImageResource> image)
    : TiledObject(startPos)
    , _power(power)
    , _attack(attack)
    , _range(range)
    , _shooterType(type)
    , _speed(speed * TILE_SCALE)
{
    _name = "skill_shoot";

    switch (direction)
    {
    case TiledVector::Direction::FORWARD:
        _moveVec = Vector2D::down;
        break;

    case TiledVector::Direction::BACK:
        _moveVec = Vector2D::up;
        break;

    case TiledVector::Direction::LEFT:
        _moveVec = Vector2D::left;
        break;

    case TiledVector::Direction::RIGHT:
        _moveVec = Vector2D::right;
        break;
    }

    _moveVec *= _speed;
    _position += Vector2D(8 * TILE_SCALE, 8 * TILE_SCALE);

    /*
    if (_shooterType == TiledObject::Type::ENEMY)
        _graph.Load("resourse/graph/tiledObject/magicBall_R.png");
    else
        _graph.Load("resourse/graph/tiledObject/magicBall_B.png");
    */
    _graph.SetResource(image);
    _graph.SetScale(Vector2D(TILE_SCALE, TILE_SCALE));
}


MagicBall::~MagicBall()
{
}


void MagicBall::Update()
{
    GraphicalObject::Update();
    Move();
    CheckHit();

    if (!FIELD->IsInside(GetTilePos()))
        OBJECT_MGR->Remove(this);

    _graph.SetPosition(_position);
}


void MagicBall::Move()
{
    _position += _moveVec;
    auto tilePos = TiledVector::ConvertToTiledPos(_position);

    if (FIELD->IsMovableThere(tilePos, *this))
        FIELD->MoveObject(*this, tilePos);
}


void MagicBall::CheckHit()
{
    auto objects = OBJECT_MGR->GetContainedObjects<TiledObject>(_position);
    auto opponentType = (_shooterType == Type::ENEMY) ? Type::MONSTER : Type::ENEMY;
    bool hasHit = false;
    
    if (objects.size() == 0)
        return;

    for (auto obj : objects)
    {
        if (!obj->IsEnable())
            continue;

        if (obj->GetType() == opponentType)
        {
            auto chara = dynamic_cast<Character*>(obj);
            chara->Damaged(20);
            hasHit = true;
            break;
        }

        if (obj->GetType() == Type::BATTLE)
        {
            auto battle = dynamic_cast<BattlingTile*>(obj);

            if (opponentType == Type::ENEMY)
                battle->MagicalAttack(_power, _attack);
            else
                battle->MagicalDamaged(_power, _attack);

            hasHit = true;
            break;
        }

        if (obj->GetType() == Type::BLOCK)
        {
            hasHit = true;
            break;
        }
    }

    if (hasHit)
        OBJECT_MGR->Remove(this);
}


bool MagicBall::IsOverwritable(TiledObject* overwriter)
{
    return true;
}