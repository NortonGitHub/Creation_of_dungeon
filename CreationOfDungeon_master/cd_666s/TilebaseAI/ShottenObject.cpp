#include "ShottenObject.h"
#include "TiledObjectMnager.h"
#include "TileField.h"

#include "Character.h"
#include "BattlingTile.h"
#include "BattleCaliculate.h"

#include "../DebugDraw.h"

ShottenObject::ShottenObject(int power, int attack, int range, double speed, TiledVector startPos, TiledVector::Direction direction, TiledObject::Type type, std::shared_ptr<ImageResource> image, bool isPhysical)
    : TiledObject(startPos)
    , _power(power)
    , _attack(attack)
    , _range(range)
    , _shooterType(type)
    , _speed(speed * TILE_SCALE)
    , _isPhysical(isPhysical)
    , _hasHit(false)
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

    //生成時隣接マスと衝突判定される不具合を回避
    _position += Vector2D(1, 1);

    _graph.SetResource(image);

    auto notmalAnimation = std::make_shared<GraphArray>();
    int divNum = _graph.GetSize()._x / _graph.GetSize()._y;
    notmalAnimation->Set(&_graph, 32, 32, divNum, 8);
    _animator.AddAnimation("normal", std::make_shared<GraphArray>(&_graph, 32, 32, divNum, 8));

    // TODO : 衝突後の炎用のオブジェクト作成
    if (_shooterType == TiledObject::Type::ENEMY
        && !_isPhysical)
    {
        _graph.SetPriority(Sprite::Priority::UI);

        _animator.AddAnimation("hit", std::make_shared<GraphArray>("resource/graph/effect/fire.png", 32, 32, 5, 15));
        _sound.Load("resource/sound/flame.wav");
    }
    else
    {
        _sound.Load("resource/sound/enemy_fall2.wav");
    }

    _animator.Transform([&](GraphArray* animation)
    {
        animation->GetGraphPtr()->SetScale(Vector2D(TILE_SCALE, TILE_SCALE));
    
	});

	_type = TiledObject::Type::ATTACK;

}


ShottenObject::~ShottenObject()
{
}


void ShottenObject::Update()
{
    GraphicalObject::Update();

    if (!_hasHit)
    {
        Move();
        CheckHit();

        if (!FIELD->IsInside(GetTilePos()))
            OBJECT_MGR->Remove(this);

        _graph.SetPosition(_position);
        //_graphArray.Update();
        _animator.Transform([&](GraphArray* animation)
        {
            animation->GetGraphPtr()->SetPosition(_position);
        });
    }
    else
    {
        bool isErasable = (!_sound.IsPlaying());
        if (_shooterType == TiledObject::Type::ENEMY
            && !_isPhysical)
            isErasable &= _animator.GetCurrentAnimation()->HasEndedUp();

        if (isErasable)
            OBJECT_MGR->Remove(this);
    }
    _animator.Update();

    if (_animator.GetCurrentAnimationName() == "hit")
    {
        if(_animator.GetCurrentAnimation()->HasEndedUp()
            && !_sound.IsPlaying())
            OBJECT_MGR->Remove(this);
    }
}


void ShottenObject::Move()
{
    _position += _moveVec;
    auto tilePos = TiledVector::ConvertToTiledPos(_position);

    if (FIELD->IsMovableThere(tilePos, *this))
        FIELD->MoveObject(*this, tilePos);
}


void ShottenObject::CheckHit()
{
    auto objects = OBJECT_MGR->GetContainedObjects<TiledObject>(_position);
    auto opponentType = (_shooterType == Type::ENEMY) ? Type::MONSTER : Type::ENEMY;
    Vector2D targetPos;
    bool hitObstacle = false;
    
    if (objects.size() == 0)
        return;

    for (auto obj : objects)
    {
        if (!obj->IsEnable())
            continue;

        if (obj->GetType() == opponentType)
        {
            auto chara = dynamic_cast<Character*>(obj);
            chara->Damaged(Battle::GetDamage(_power, _attack, _isPhysical, *chara));
            targetPos = chara->GetPosition();
            _hasHit = true;
            break;
        }

        if (obj->GetType() == Type::BATTLE)
        {
            auto battle = dynamic_cast<BattlingTile*>(obj);
            battle->AttackFromOutside(_power, _attack, _isPhysical, opponentType);
            targetPos = battle->GetPosition();
            _hasHit = true;
            break;
        }

        if (!obj->IsOverwritable(this))
        {
            _hasHit = true;
            hitObstacle = true;
            break;
        }
    }

    if (_hasHit)
    {
        if (hitObstacle)
        {
            OBJECT_MGR->Remove(this);
            return;
        }

        if (_shooterType == TiledObject::Type::ENEMY
            && !_isPhysical)
            _animator.SwitchWithReset("hit");

        _sound.Play();
        _position = targetPos;
    }
}


bool ShottenObject::IsOverwritable(TiledObject* overwriter)
{
    return true;
}