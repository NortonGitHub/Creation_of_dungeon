#include "ShootDamageObject.h"
#include "Character.h"
#include "ShottenObject.h"

#include "TiledObjectMnager.h"
#include "TileField.h"


ShootDamageObject::ShootDamageObject(double power, int cost, double startRatio, double speed, int range, Character& chara, bool isPhysical)
    : CharactersSkill(cost, startRatio)
    , _character(chara)
    , _power(power)
    , _range(range)
    , _speed(speed)
    , _isPhysical(isPhysical)
{
    _image = IMAGE_RESOURCE_TABLE->Create("resource/graph/effect/fire_ball.png");
}


ShootDamageObject::~ShootDamageObject()
{
}


bool ShootDamageObject::ShouldActivate()
{
    auto tilePos = _character.GetTilePos();
    auto type = _character.GetType();
    auto opponentType = (type == TiledObject::Type::ENEMY) ? TiledObject::Type::MONSTER : TiledObject::Type::ENEMY;
    auto direction = _character.GetDirection();

    //方向に対応したベクトルを算出して
    TiledVector directionVec(0, 0);
    switch (direction)
    {
    case TiledVector::Direction::FORWARD:
        directionVec = TiledVector::up;
        break;

    case TiledVector::Direction::BACK:
        directionVec = TiledVector::down;
        break;

    case TiledVector::Direction::LEFT:
        directionVec = TiledVector::left;
        break;

    case TiledVector::Direction::RIGHT:
        directionVec = TiledVector::right;
        break;
    }

    //射程距離だけ調べる
    std::vector<TiledVector> searchTilePoses(_range + 1);
    for (int i = 1; i <= _range; ++i)
    {
        searchTilePoses[i] = tilePos + directionVec * i;
        auto objects = FIELD->GetTiledObjects(searchTilePoses[i]);
        for (auto obj : objects)
        {
            if (!obj->IsEnable())
                continue;

            if (obj->GetType() == opponentType
                || obj->GetType() == TiledObject::Type::BATTLE)
            {
                return true;
            }
        }
    }

    return false;
}


void ShootDamageObject::Activate()
{
    if (_mp < _mpCost)
        return;

    auto tilePos = _character.GetTilePos();
    auto type = _character.GetType();
    auto direction = _character.GetDirection();
    auto param = _character.GetAffectedParameter();

    if (_isPhysical && type == TiledObject::Type::ENEMY)
    {
        switch (direction)
        {
        case TiledVector::Direction::FORWARD:
            _image = IMAGE_RESOURCE_TABLE->Create("resource/graph/trap/arrow_down.png");
            break;

        case TiledVector::Direction::BACK:
            _image = IMAGE_RESOURCE_TABLE->Create("resource/graph/trap/arrow_up.png");
            break;

        case TiledVector::Direction::LEFT:
            _image = IMAGE_RESOURCE_TABLE->Create("resource/graph/trap/arrow_left.png");
            break;

        case TiledVector::Direction::RIGHT:
            _image = IMAGE_RESOURCE_TABLE->Create("resource/graph/trap/arrow_right.png");
            break;
        }
    }

    int attack = (_isPhysical) ? param._attack : param._magicAttack;
    OBJECT_MGR->Add(std::make_shared<ShottenObject>(_power, attack, _range, _speed, tilePos, direction, type, _image, _isPhysical));

    _mp = 0;
}