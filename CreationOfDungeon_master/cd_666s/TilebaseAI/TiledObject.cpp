#include "TiledObject.h"
#include "MapTile.h"
#include "TileField.h"
#include "../InputManager/MouseInput.h"

TiledObject::TiledObject(TiledVector pos)
: _tile(nullptr)
, _type(Type::DEFAULT)
{
    FIELD->RegistObject(*this, pos);
}


TiledObject::~TiledObject()
{
    if (_tile != nullptr)
        FIELD->RemoveObject(*this);
}


TiledVector TiledObject::GetTilePos() const
{
    if (_tile == nullptr)
        return TiledVector::zero;
    
    return _tile->GetTilePos();
}


void TiledObject::Init() 
{
    _graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
}


void TiledObject::Interact(Character& character)
{
}


void TiledObject::OnClicked()
{
}


void TiledObject::CheckClicked()
{
    if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
    {
        auto cursorPos = MOUSE->GetCursorPos();
        if (TiledVector::ConvertToTiledPos(cursorPos) == _tile->GetTilePos())
            OnClicked();
    }
}