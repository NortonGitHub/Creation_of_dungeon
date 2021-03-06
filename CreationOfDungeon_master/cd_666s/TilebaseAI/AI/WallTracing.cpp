#include "WallTracing.h"
#include "../Character.h"
#include "../TileField.h"
#include "../../DebugDraw.h"

WallTracing::WallTracing(Character &owner, std::vector<TiledVector>& pathRef)
: PathFindingAIBase(owner, pathRef)
, _direction(1, 0)
{
}


WallTracing::~WallTracing()
{
}


void WallTracing::Reset()
{
}


void WallTracing::Update()
{
    Trace();
}


void WallTracing::Trace()
{
    TiledVector pos = _owner.GetTilePos();
    
    
    //左後ろが壁で、左が壁でないなら
    if (!FIELD->IsMovableThere(pos + _direction.GetRotated(TiledVector::Direction::LEFT) - _direction, _owner)
        &&   FIELD->IsMovableThere(pos + _direction.GetRotated(TiledVector::Direction::LEFT), _owner))
    {
        //左へ回転
        _direction.Rotate(TiledVector::Direction::LEFT);
    }
    //正面が壁なら
    else if (!FIELD->IsMovableThere(pos + _direction, _owner))
    {
        //右へ回転
        _direction.Rotate(TiledVector::Direction::RIGHT);
    }
    
    //回転後の向きを正面とみなす
    _pathRef.push_back(pos + _direction);
}


void WallTracing::Draw()
{
    auto pos = _owner.GetTilePos();
    Vector2D v = (pos + _direction).GetWorldPos();
    Vector2D v2 = (pos - _direction + _direction.GetRotated(TiledVector::Direction::LEFT)).GetWorldPos();
    Vector2D v3 = (pos + _direction.GetRotated(TiledVector::Direction::LEFT)).GetWorldPos();
    
    Debug::DrawRectWithSize(v, Vector2D(TILE_SIZE, TILE_SIZE), Color4(0.0, 0.5, 1.0, 0.5), true);
    Debug::DrawRectWithSize(v2, Vector2D(TILE_SIZE, TILE_SIZE), Color4(1.0, 0.5, 0.0, 0.5), true);
    Debug::DrawRectWithSize(v3, Vector2D(TILE_SIZE, TILE_SIZE), Color4(1.0, 0.5, 0.0, 0.5), true);
}