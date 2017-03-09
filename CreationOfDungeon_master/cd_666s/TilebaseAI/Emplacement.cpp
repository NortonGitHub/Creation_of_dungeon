#include "Emplacement.h"
#include "TileField.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "BattleCaliculate.h"
#include "../InputManager/MouseInput.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"


Emplacement::Emplacement(TiledVector pos, int cost, int power, int attack, TiledVector::Direction direction)
    : Trap(pos, cost, 5)
    , _power(power)
    , _attack(attack)
    , _shootDirection(direction)
{
    _graph.Load("resourse/graph/item/block.png");
}


Emplacement::~Emplacement()
{
}


void Emplacement::Activate()
{
    Trap::Activate();

    //ŽË’ö•ûŒü‚©‚ç’²‚×‚é”ÍˆÍ‚ðŒˆ’è
    auto fieldSize = FIELD->GetFieldSize();
    TiledVector move;
    int distance = 0;
    switch (_shootDirection)
    {
    case TiledVector::Direction::LEFT:
        distance = fieldSize._x;
        move = TiledVector::left;
        break;

    case TiledVector::Direction::RIGHT:
        distance = fieldSize._x;
        move = TiledVector::right;
        break;

    case TiledVector::Direction::FORWARD:
        distance = fieldSize._y;
        move = TiledVector::up;
        break;


    case TiledVector::Direction::BACK:
        distance = fieldSize._y;
        move = TiledVector::down;
        break;
    }

    TiledVector tilePos = GetTilePos();
    for (int i = 0; i < distance; ++i)
    {
        auto pos = tilePos;
        pos += (move * i);

        //‚»‚ÌêŠ‚ÉáŠQ•¨‚ª‚ ‚Á‚½‚çI—¹
        auto obstacle = FIELD->GetTiledObject<Obstacle>(pos);
        if (obstacle != nullptr)
            return;

        auto targets = FIELD->GetTiledObjects<Enemy>(pos);
        for (auto target : targets)
        {
            if (!target->IsEnable())
                continue;

            auto param = target->GetAffectedParameter();
            target->Damaged(Battle::GetPhysicalAttackDamage(_power, _attack, param._defence));
            return;
        }
    }
}


bool Emplacement::IsActivatable() const
{
    if (!Trap::IsActivatable())
        return false;

    if (!MOUSE->DoubleClicked())
        return false;

    return (Contain(MOUSE->GetCursorPos()));
}
