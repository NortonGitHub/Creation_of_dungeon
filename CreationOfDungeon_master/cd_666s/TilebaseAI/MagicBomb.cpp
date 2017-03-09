#include "MagicBomb.h"
#include "Enemy.h"
#include "TileField.h"
#include "BattleCaliculate.h"
#include "../InputManager/MouseInput.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"


MagicBomb::MagicBomb(TiledVector trapPos, int cost, int range, int power, int attack)
    : Trap(trapPos, cost, 5)
    , _range(range)
    , _power(power)
    , _attack(attack)
{
    _graph.Load("resourse/graph/trap/mine.png");
    _graph.SetPriority(200);
    _graph.SetPosition(_position);
    _graphArray.Set(&_graph, 32, 32, 8, 32);
    _graphArray._isLoop = false;
    _graphArray._isPlaying = false;
}


MagicBomb::~MagicBomb()
{
}



void MagicBomb::Activate()
{
    Trap::Activate();

    TiledVector tilePos = GetTilePos();
    for (int i = -_range; i <= _range; ++i)
    {
        for (int k = -_range; k <= _range; ++k)
        {
            auto pos = tilePos + TiledVector(i, k);
            auto targets = FIELD->GetTiledObjects<Enemy>(pos);

            for (auto target : targets)
            {
                if (!target->IsEnable())
                    continue;

                auto param = target->GetAffectedParameter();
                target->Damaged(Battle::GetPhysicalAttackDamage(_power, _attack, param._magicDefence));
            }
        }
    }
}


bool MagicBomb::IsActivatable() const
{
    if (!Trap::IsActivatable())
        return false;

    if (!MOUSE->DoubleClicked())
        return false;

    return (Contain(MOUSE->GetCursorPos()));
}