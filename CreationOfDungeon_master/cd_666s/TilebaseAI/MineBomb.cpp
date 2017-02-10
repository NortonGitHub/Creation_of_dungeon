#include "MineBomb.h"
#include "MapTile.h"
#include "Enemy.h"
#include "../DebugDraw.h"
#include "TiledObjectMnager.h"

MineBomb::MineBomb(TiledVector trapPos)
    : Trap(trapPos, 220, 220, 5)
    , _range(1)
    , _damage(50)
{
    _name = "mine";
    _graph.Load("resourse/graph/tiledObject/mine.png");
    _graph.SetPriority(200);
    _graph.SetPosition(_position);
    _graphArray.Set(&_graph, 32, 32, 8, 32);
    _graphArray._isLoop = false;
    _graphArray._isPlaying = false;
}


MineBomb::~MineBomb()
{
}


void MineBomb::Update()
{
    Trap::Update();
    auto objects = GetTile().lock()->GetTiledObjects();
    Character* target = nullptr;

    bool needActivate = false;
    for (auto obj : objects)
    {
        if (obj->GetType() != Type::ENEMY)
            continue;

        //àÍíËãóó£Ç‹Ç≈ãﬂÇ√Ç¢ÇΩÇÁî≠ìÆ
        auto distance = (obj->GetPosition() - _position).GetLength();
        if (TILE_SIZE / 2 < distance)
            continue;

        target = dynamic_cast<Character*>(obj);
        needActivate = true;
        break;
    }

    if (needActivate && IsEnable())
    {
        _graphArray._isPlaying = true;
        _duravity -= _cost;
        target->Damaged(_damage);
    }
}


void MineBomb::Draw()
{
    _graphArray.Update();

    bool display = (!_graphArray.HasEndedUp() || IsEnable());

    //îºìßñæÇ…Ç∑ÇÈÇ©Ç«Ç§Ç©
    float alpha = (display) ? 1.0 : 0.35;
    _graph.GetTexturePtr().lock()->SetBaseColor(Color4(1, 1, 1, alpha));

    //ëœãvóÕÉQÅ[ÉWÇï\é¶Ç∑ÇÈÇ©
    if (!display)
    {
        double ratio = static_cast<double>(_duravity) / static_cast<double>(_maxDuravity);
        Debug::DrawRectWithSize(_position + Vector2D(-16, 0), Vector2D(64, 8), ColorPalette::BLACK4, false);
        Debug::DrawRectWithSize(_position + Vector2D(-16, 0), Vector2D(64 * ratio, 8), ColorPalette::BLUE4, true);
    }
}


bool MineBomb::IsEnable() const
{
    return (_maxDuravity == _duravity);
}