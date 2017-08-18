#include "GraphicalObject.h"

GraphicalObject::GraphicalObject()
: _graph()
{
}


GraphicalObject::~GraphicalObject()
{
}


void GraphicalObject::Update()
{
}


void GraphicalObject::Draw()
{
    _graph.SetPosition(_position);
}


bool GraphicalObject::Contain(Vector2D pos) const
{
    auto texturePtr = _graph.GetTexturePtr();
    if (texturePtr.expired())
        return false;
    
    auto texture = texturePtr.lock();
    auto size = texture->GetBaseSize();
    if (pos._x < _position._x)
        return false;
    if (pos._y < _position._y)
        return false;
    if (_position._x + size._x < pos._x)
        return false;
    if (_position._y + size._y < pos._y)
        return false;
    
    return true;
}