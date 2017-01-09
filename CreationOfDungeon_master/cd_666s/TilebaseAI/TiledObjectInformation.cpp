#include "TiledObjectInformation.h"
#include "ObjectInformationDrawer.h"
#include "Character.h"
#include "../DebugDraw.h"


TiledObjectInformation::TiledObjectInformation(Vector2D position)
    : _position(position)
    , _character(nullptr)
    , _enemyThumbnail("graph/enemy_thumbnail.png", position)
    , _allyThumbnail("graph/ally_thumbnail.png", position)
{
    _icon.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("blaver")));
    _icon.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("magician")));
    _icon.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("fighter")));
    _icon.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("bone")));
    _icon.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("ghost")));
    _icon.push_back(new Sprite(ObjectInformationDrawer::GetIconNameFromName("minotaur")));

    _enemyThumbnail.SetDisplayMode(false);
    _allyThumbnail.SetDisplayMode(false);

    _enemyThumbnail.SetPriority(100);
    _allyThumbnail.SetPriority(100);

}


TiledObjectInformation::~TiledObjectInformation()
{
    Clear();
}


void TiledObjectInformation::Init()
{
    for (auto icon : _icon)
    {
        icon->SetDisplayMode(false);
        icon->SetPriority(1090);
        icon->SetPosition(_position + Vector2D(140, 32));
    }
}


void TiledObjectInformation::Clear()
{
    for (auto icon : _icon)
    {
        if (icon == nullptr)
            continue;

        delete icon;
        icon = nullptr;
    }
    _icon.clear();
    _icon.resize(0);
}


void TiledObjectInformation::Draw()
{
    if (_character != nullptr)
    {
        bool isEnemy = (_character->GetType() == TiledObject::Type::ENEMY);

        _enemyThumbnail.SetDisplayMode(isEnemy);
        _allyThumbnail.SetDisplayMode(!isEnemy);

        DrawInformation(_character);

        for (auto icon : _icon)
        {
            icon->SetDisplayMode(false);
            icon->SetPriority(100);
        }

        Sprite* iconPtr = _icon[ObjectInformationDrawer::GetIndexFromName(_character->GetName())];
        iconPtr->SetScale(Vector2D(2, 2));
        iconPtr->SetDisplayMode(true);
    }
    else
    {
        _enemyThumbnail.SetDisplayMode(false);
        _allyThumbnail.SetDisplayMode(false);

        for (auto icon : _icon)
        {
            icon->SetDisplayMode(false);
            icon->SetPriority(100);
        }
    }
}


void TiledObjectInformation::DrawInformation(Character* chara)
{
    const Character::BattleParameter& param = chara->_battleParameter;

    auto color = (chara->GetType() == TiledObject::Type::ENEMY) ? ColorPalette::RED4 : ColorPalette::BLUE4;
    Vector2D hpOffset(110, 130);
    Debug::DrawString(_position + hpOffset, "HP");
    Debug::DrawRectWithSize(_position + hpOffset + Vector2D(24, 0), Vector2D(param._hp / double(chara->_maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(_position + hpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    std::string paramStr = "ATK : ";
    paramStr += std::to_string(param._attack);
    Debug::DrawString(_position + Vector2D(90, 170), paramStr);

    paramStr = "DEF : ";
    paramStr += std::to_string(param._defence);
    Debug::DrawString(_position + Vector2D(190, 170), paramStr);

    paramStr = "MATK : ";
    paramStr += std::to_string(param._attack);
    Debug::DrawString(_position + Vector2D(90, 200), paramStr);

    paramStr = "MDEF : ";
    paramStr += std::to_string(param._defence);
    Debug::DrawString(_position + Vector2D(180, 200), paramStr);

    paramStr = "SPD : ";
    paramStr += std::to_string(param._speed);
    Debug::DrawString(_position + Vector2D(130, 230), paramStr);
}