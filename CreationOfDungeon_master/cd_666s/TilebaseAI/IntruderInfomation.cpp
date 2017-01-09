#include "IntruderInfomation.h"
#include "ObjectInformationDrawer.h"
#include "StartPoint.h"
#include "Character.h"
#include "../DebugDraw.h"

IntruderInfomation::IntruderInfomation()
    : _position(754, 248)
{
    _icons.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("blaver")));
    _icons.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("magician")));
    _icons.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("fighter")));
    _icons.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("bone")));
    _icons.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("ghost")));
    _icons.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("minotaur")));

    for (auto icon : _icons)
    {
        icon->SetPriority(101);
        icon->SetDisplayMode(false);
        icon->SetPosition(Vector2D(754 + 30, 248 + 175));
    }
}


IntruderInfomation::~IntruderInfomation()
{
    for (auto icon : _icons)
    {
        delete icon;
    }
}


void IntruderInfomation::InitWithSetup(StartPoint* intrudePoint)
{
    _intrudePoint = nullptr;
    if (intrudePoint == nullptr)
        return;

    _intrudePoint = intrudePoint;
}


void IntruderInfomation::Draw()
{
    //ŽŸ‚ÉN“ü‚·‚é“G‚Ìî•ñ
    for (auto icon : _icons)
    {
        icon->SetDisplayMode(false);
    }

    Debug::DrawString(_position + Vector2D(25, 155), "NEXT");

    if (_intrudePoint == nullptr)
        return;

    if (_intrudePoint->GetTimeUnitlNext() != -1)
    {
        auto chara = _intrudePoint->GetNextEnemy();
        if (chara != nullptr)
        {
            std::string name = chara->GetName();
            _icons[ObjectInformationDrawer::GetIndexFromName(name)]->SetDisplayMode(true);
        }
        Debug::DrawString(_position + Vector2D(65, 170), "‚ ‚Æ");
        Debug::DrawString(_position + Vector2D(70, 190), std::to_string(_intrudePoint->GetTimeUnitlNext() / 60));
    }
}