#include "IntruderInfomation.h"
#include "ObjectInformationDrawer.h"
#include "StartPoint.h"
#include "Character.h"
#include "../DebugDraw.h"

IntruderInfomation::IntruderInfomation(const TiledObjectDictionary& dictionary)
    : _position(754, 248)
    , _dictionary(dictionary)
{
    _icon = std::make_unique<Sprite>();
    _icon->SetPriority(101);
    _icon->SetPosition(Vector2D(754 + 30, 248 + 175));
}


IntruderInfomation::~IntruderInfomation()
{
    _icon = nullptr;
}


void IntruderInfomation::InitWithSetup(const std::weak_ptr<StartPoint>& intrudePoint)
{
    _intrudePoint.reset();
    if (intrudePoint.expired())
        return;

    _intrudePoint = intrudePoint;
}


void IntruderInfomation::Draw()
{
    Debug::DrawString(_position + Vector2D(25, 155), "NEXT");

    if (_intrudePoint.expired())
        return;

    auto argIntrudePoint = _intrudePoint.lock();
    if (argIntrudePoint->GetTimeUnitlNext() != -1)
    {
        auto chara = argIntrudePoint->GetNextEnemy();
        if (chara != nullptr)
        {
            std::string name = chara->GetName();
            _icon->SetResource(_dictionary.GetImageFromName(name));
            _icon->SetPriority(101);
            _icon->SetPosition(Vector2D(754 + 30, 248 + 175));
        }
        Debug::DrawString(_position + Vector2D(65, 170), "‚ ‚Æ");
        Debug::DrawString(_position + Vector2D(70, 190), std::to_string(argIntrudePoint->GetTimeUnitlNext() / 60));
    }
    else
    {
        _icon->SetResource(nullptr);
    }
}