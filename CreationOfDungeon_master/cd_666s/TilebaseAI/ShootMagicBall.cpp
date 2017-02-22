#include "ShootMagicBall.h"
#include "Character.h"
#include "MagicBall.h"

#include "TiledObjectMnager.h"
#include "TileField.h"

ShootMagicBall::ShootMagicBall(double power, int cost, Character& chara, int range)
    : CharactersSkill(cost)
    , _character(chara)
    , _power(power)
    , _range(range)
{
}


ShootMagicBall::~ShootMagicBall()
{
}


bool ShootMagicBall::ShouldActivate()
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


void ShootMagicBall::Activate()
{
    if (_mp < _mpCost)
        return;

    auto tilePos = _character.GetTilePos();
    auto type = _character.GetType();
    auto direction = _character.GetDirection();

    int actualPower = _power * (_character.GetAffectedParameter()._magicAttack);
    OBJECT_MGR->Add(std::make_shared<MagicBall>(actualPower, _range, tilePos, direction, type));

    _mp = 0;
}