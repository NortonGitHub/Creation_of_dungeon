#include "ShootMagicBall.h"
#include "Character.h"
#include "MagicBall.h"

#include "TiledObjectMnager.h"
#include "TileField.h"


ShootMagicBall::ShootMagicBall(double power, int cost, double speed, int range, Character& chara)
    : CharactersSkill(cost)
    , _character(chara)
    , _power(power)
    , _range(range)
    , _speed(speed)
{
    _image = IMAGE_RESOURCE_TABLE->Create("resourse/graph/tiledObject/magicBall_R.png");
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

    //�����ɑΉ������x�N�g�����Z�o����
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

    //�˒������������ׂ�
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

    int magicAttack = _character.GetAffectedParameter()._magicAttack;
    OBJECT_MGR->Add(std::make_shared<MagicBall>(_power, magicAttack, _range, _speed, tilePos, direction, type, _image));

    _mp = 0;
}