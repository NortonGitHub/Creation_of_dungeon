#include "Sanctuary.h"
#include "Monster.h"
#include "TileField.h"
#include "../InputManager/MouseInput.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

Sanctuary::Sanctuary(TiledVector pos, int range, int cost, ParameterMultiplier multiplier)
    : Trap(pos, cost, 5)
    , _range(1)
    , _multiplier(std::move(multiplier))
{
    _graph.Load("resourse/graph/trap/Sanctuary.png");
}


Sanctuary::~Sanctuary()
{
}


void Sanctuary::Activate()
{
    Trap::Activate();

    TiledVector tilePos = GetTilePos();
    for (int i = -_range; i <= _range; ++i)
    {
        for (int k = -_range; k <= _range; ++k)
        {
            auto pos = tilePos + TiledVector(i, k);
            auto targets = FIELD->GetTiledObjects<Monster>(pos);

            for (auto target : targets)
            {
                if (!target->IsEnable())
                    continue;

                target->AddParameterEffecter(std::make_unique<ParameterMultiplier>(_multiplier));
            }
        }
    }
}


bool Sanctuary::IsActivatable() const
{
    if (!Trap::IsActivatable())
        return false;

    if (!MOUSE->DoubleClicked())
        return false;

    return (Contain(MOUSE->GetCursorPos()));
}
