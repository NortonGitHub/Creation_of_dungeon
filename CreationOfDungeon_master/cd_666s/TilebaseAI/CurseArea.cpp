#include "CurseArea.h"
#include "Enemy.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"

CurseArea::CurseArea(TiledVector pos, int cost, ParameterMultiplier multiplier)
    : Trap(pos, cost, 5)
    , _multiplier(std::move(multiplier))
{
    _graph.Load("resourse/graph/trap/CurseArea.png");
}


CurseArea::~CurseArea()
{
}


void CurseArea::Activate()
{
    if (_targetCache == nullptr)
        return;

    Trap::Activate();
    _targetCache->AddParameterEffecter(std::make_unique<ParameterMultiplier>(_multiplier));
}


bool CurseArea::IsActivatable() const
{
    if (!Trap::IsActivatable())
        return false;

    bool isOverrided = false;

    //“G‚ªŽ©•ª‚Ìƒ}ƒX‚É‚¢‚é‚©‚Ç‚¤‚©
    Enemy* target = GetTile().lock()->GetTiledObject<Enemy>();
    if (target != nullptr)
    {
        //ˆê’è‹——£‚Ü‚Å‹ß‚Ã‚¢‚½‚ç”­“®
        auto distance = (target->GetPosition() - _position).GetLength();
        if (distance < TILE_SIZE / 4)
        {
            isOverrided = true;
            _targetCache = target;
        }
    }

    return isOverrided;
}
