#include "TiledObjectInformation.h"
#include "ObjectInformationDrawer.h"
#include "Character.h"
#include "../DebugDraw.h"


TiledObjectInformation::TiledObjectInformation(const TiledObjectDictionary& iconDictionary, Vector2D position)
    : _position(position)
    , _character(nullptr)
    , _iconDictionary(iconDictionary)
    , _enemyThumbnail("resourse/graph/enemy_thumbnail.png", position)
    , _allyThumbnail("resourse/graph/ally_thumbnail.png", position)
{
    _icon = std::make_unique<Sprite>();

    _enemyThumbnail.SetDisplayMode(false);
    _allyThumbnail.SetDisplayMode(false);

    _enemyThumbnail.SetPriority(Sprite::Priority::UI);
    _allyThumbnail.SetPriority(Sprite::Priority::UI);

}


TiledObjectInformation::~TiledObjectInformation()
{
    Clear();
}


void TiledObjectInformation::Init()
{
    if (_icon == nullptr)
        return;
    
    _icon->SetDisplayMode(true);
    _icon->SetPriority(1090);
    _icon->SetScale({ 2, 2 });
    _icon->SetPosition(_position + Vector2D(140, 32));
}


void TiledObjectInformation::Clear()
{
    _icon = nullptr;
    _character = nullptr;
}


void TiledObjectInformation::Draw()
{
    if (_character != nullptr)
    {
        bool isEnemy = (_character->GetType() == TiledObject::Type::ENEMY);

        _enemyThumbnail.SetDisplayMode(isEnemy);
        _allyThumbnail.SetDisplayMode(!isEnemy);

        _icon->SetResource(_iconDictionary.GetImageFromName(_character->GetName()));
        Init();

        DrawInformation(_character);
    }
    else
    {
        _enemyThumbnail.SetDisplayMode(false);
        _allyThumbnail.SetDisplayMode(false);
        _icon->SetDisplayMode(false);
    }
}


void TiledObjectInformation::DrawInformation(Character* chara)
{
    const BattleParameter& param = chara->_battleParameter;

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