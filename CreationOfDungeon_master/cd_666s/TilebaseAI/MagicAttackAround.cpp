#include "MagicAttackAround.h"
#include "Character.h"
#include "MagicExplosion.h"
#include "TiledObjectMnager.h"
#include "TileField.h"

MagicAttackAround::MagicAttackAround(double power, int cost, int range, Character& chara)
    : CharactersSkill(cost)
    , _character(chara)
    , _power(power)
    , _range(range)
{
    _image = IMAGE_RESOURCE_TABLE->Create("resourse/graph/tiledObject/explosion.png");
}


MagicAttackAround::~MagicAttackAround()
{
}


bool MagicAttackAround::ShouldActivate()
{
    auto tilePos = _character.GetTilePos();
    auto type = _character.GetType();
    auto opponentType = (type == TiledObject::Type::ENEMY) ? TiledObject::Type::MONSTER : TiledObject::Type::ENEMY;

    //”ÍˆÍ“à‚É‰½‚©‚ ‚é‚©’²‚×‚é
    TiledVector pos;
    for (int i = -_range; i <= _range; ++i)
    {
        for (int k = -_range; k <= _range; ++k)
        {
            pos = tilePos + TiledVector(i, k);
            auto objects = FIELD->GetTiledObjects(pos);

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
    }

    return false;
}


void MagicAttackAround::Activate()
{
    if (_mp < _mpCost)
        return;

    auto tilePos = _character.GetTilePos();
    auto type = _character.GetType();
    int magicAttack = _character.GetAffectedParameter()._magicAttack;
    OBJECT_MGR->Add(std::make_shared<MagicExplosion>(_power, magicAttack, _range, tilePos, type, _image));

    _mp = 0;
}