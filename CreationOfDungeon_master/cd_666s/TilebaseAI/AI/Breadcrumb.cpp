#include "Breadcrumb.h"
#include "../TileField.h"
#include "../../DebugDraw.h"

Breadcrumb::Breadcrumb(TiledVector tile, int lifeTime)
    : _pos(tile)
    , _time(0)
    , _lifeTime(lifeTime)
    , _id(0)
{
    static int totalID = 0;
    totalID++;

    _id = totalID;
}


Breadcrumb::~Breadcrumb()
{
}


void Breadcrumb::Update()
{
    _time++;

    if (_time < _lifeTime)
        return;

    _time = 0;
    FIELD->RemoveBreadcrumb(this);
}


void Breadcrumb::Draw()
{
    auto pos = GetTilePos().GetWorldPos();
    Debug::DrawString(pos, std::to_string(_id));
}