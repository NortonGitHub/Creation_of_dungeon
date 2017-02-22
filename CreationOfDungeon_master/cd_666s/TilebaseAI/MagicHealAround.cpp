#include "MagicHealAround.h"
#include "TiledObjectMnager.h"
#include "TileField.h"

#include "Character.h"
#include "Monster.h"
#include "Enemy.h"
#include "BattlingTile.h"

MagicHealAround::MagicHealAround(double power, int cost, Character& chara, int range)
    : CharactersSkill(cost)
    , _character(chara)
    , _power(power)
    , _range(range)
{
    _targetsCache.reserve(6);
}


MagicHealAround::~MagicHealAround()
{
}


bool MagicHealAround::ShouldActivate()
{
    if (_mp < _mpCost)
        return false;

    auto tilePos = _character.GetTilePos();
    auto type = _character.GetType();

    //”ÍˆÍ“à‚É‰½‚©‚ ‚é‚©’²‚×‚é
    TiledVector pos;
    _targetsCache.resize(0);
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

                Character* chara = nullptr;
                if (obj->GetType() == type)
                {
                    chara = dynamic_cast<Character*>(obj);
                }
                else if (obj->GetType() == TiledObject::Type::BATTLE)
                {
                    auto battle = dynamic_cast<BattlingTile*>(obj);
                    if (type == TiledObject::Type::ENEMY)
                        chara = &battle->_enemy;
                    else
                        chara = &battle->_monster;
                }
                else
                    continue;

                if (_targetsCache.size() == 0)
                {
                    auto objParam = chara->GetAffectedParameter();
                    if (objParam._maxHP / 2 < objParam._hp)
                        continue;
                }

                _targetsCache.push_back(chara);
            }
        }
    }

    return (0 < _targetsCache.size());
}


void MagicHealAround::Activate()
{
    for (auto target : _targetsCache)
    {
        target->Damaged(-100 * _power);
    }

    _mp = 0;
}