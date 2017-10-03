#include "CharacterInfomationDisplayer.h"
#include "MapTile.h"

CharacterInfomationDisplayer::CharacterInfomationDisplayer(Vector2D& positionRef, Effecters& effecters)
    : _effecters(effecters)
    , _characterPos(positionRef)
    , _displayCounter(0)
{
    _statusUp.Load("resource/graph/icon/status_up.png");
    _statusDown.Load("resource/graph/icon/status_down.png");

    _statusUp.SetPriority(Sprite::Priority::UI);
    _statusDown.SetPriority(Sprite::Priority::UI);
}


CharacterInfomationDisplayer::~CharacterInfomationDisplayer()
{
}


void CharacterInfomationDisplayer::Update()
{
    bool hasPositiveEffecter = false;
    bool hasNegativeEffecter = false;

    for (auto& effecter : _effecters)
    {
        if (!hasPositiveEffecter)
            hasPositiveEffecter = effecter->IsPositive();

        if (!hasNegativeEffecter)
            hasNegativeEffecter = !effecter->IsPositive();
    }

    //カウンタでどちらかしか表示しないようにフィルタリングする
    if (hasPositiveEffecter && hasNegativeEffecter)
    {
        _displayCounter++;

        if (_displayCounter < 30)
        {
            hasPositiveEffecter = false;
        }
        else
        {
            hasNegativeEffecter = false;
        }

        if (60 < _displayCounter)
            _displayCounter = 0;
    }

    _statusUp.SetDisplayMode(hasPositiveEffecter);
    _statusDown.SetDisplayMode(hasNegativeEffecter);

    auto graphSize = _statusUp.GetSize();
    _statusUp.SetPosition(_characterPos + Vector2D(TILE_SIZE - graphSize._x, TILE_SIZE - graphSize._y));
    _statusDown.SetPosition(_characterPos + Vector2D(TILE_SIZE - graphSize._x, TILE_SIZE - graphSize._y));
}