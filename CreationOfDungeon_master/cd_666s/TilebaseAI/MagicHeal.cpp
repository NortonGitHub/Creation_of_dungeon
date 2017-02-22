#include "MagicHeal.h"
#include "TiledObjectMnager.h"
#include "TileField.h"

#include "Character.h"
#include "Monster.h"
#include "Enemy.h"
#include "BattlingTile.h"

MagicHeal::MagicHeal(double power, int cost, Character& chara, int range)
    : CharactersSkill(cost)
    , _character(chara)
    , _range(range)
    , _power(power)
    , _targetCache(nullptr)
{
}


MagicHeal::~MagicHeal()
{
}


bool MagicHeal::ShouldActivate()
{
    if (_mp < _mpCost)
        return false;

    auto tilePos = _character.GetTilePos();
    auto type = _character.GetType();

    //�͈͓��ɉ������邩���ׂ�
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

                auto objParam = chara->GetAffectedParameter();
                if (objParam._maxHP / 2 < objParam._hp)
                    continue;
                
                _targetCache = chara;
                return true;
            }
        }
    }

    return false;
}


void MagicHeal::Activate()
{
    if (_targetCache == nullptr)
        return;

    _targetCache->Damaged(-100 * _power);
    _mp = 0;
}