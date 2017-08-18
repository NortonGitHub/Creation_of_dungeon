#include "MagicBomb.h"
#include "Enemy.h"
#include "TileField.h"
//#include "BattleCaliculate.h"
#include "MagicExplosion.h"
#include "TiledObjectMnager.h"

#include "../InputManager/MouseInput.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"


MagicBomb::MagicBomb(TiledVector trapPos, int cost, int range, int power, int attack)
    : Trap(trapPos, cost, 5)
    , _range(range)
    , _power(power)
    , _attack(attack)
{
    _graph.Load("graph/trap/mine_R.png");
    _graph.SetPriority(200);
    _graph.SetPosition(_position);
    _graphArray.Set(&_graph, 32, 32, 8, 32);
    _graphArray._isLoop = false;
    _graphArray._isPlaying = false;

    _image = IMAGE_RESOURCE_TABLE->Create("graph/effect/explosion_B.png");
}


MagicBomb::~MagicBomb()
{
}



void MagicBomb::Activate()
{
    Trap::Activate();
    OBJECT_MGR->Add(std::make_shared<MagicExplosion>(_power, _attack, _range, GetTilePos(), Type::MONSTER, _image));
}


bool MagicBomb::IsActivatable() const
{
    if (!Trap::IsActivatable())
        return false;

    if (!MOUSE->DoubleClicked())
        return false;

    return (Trap::Contained(_graphArray, MOUSE->GetCursorPos()));
}