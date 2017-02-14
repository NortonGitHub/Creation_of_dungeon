#include "TiledObjectInformation.h"
#include "ObjectInformationDrawer.h"
#include "Character.h"
#include "Monster.h"
#include "Enemy.h"
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

        _character->DrawParameter(_position);
    }
    else
    {
        _enemyThumbnail.SetDisplayMode(false);
        _allyThumbnail.SetDisplayMode(false);
        _icon->SetDisplayMode(false);
    }
}


void Character::DrawParameter(Vector2D anchorPos)
{
    const BattleParameter& param = _battleParameter;

    std::string paramStr = "ATK : ";
    paramStr += std::to_string(param._attack);
    Debug::DrawString(anchorPos + Vector2D(90, 190), paramStr);

    paramStr = "DEF : ";
    paramStr += std::to_string(param._defence);
    Debug::DrawString(anchorPos + Vector2D(190, 190), paramStr);

    paramStr = "MATK : ";
    paramStr += std::to_string(param._attack);
    Debug::DrawString(anchorPos + Vector2D(90, 215), paramStr);

    paramStr = "MDEF : ";
    paramStr += std::to_string(param._defence);
    Debug::DrawString(anchorPos + Vector2D(180, 215), paramStr);

    paramStr = "SPD : ";
    paramStr += std::to_string(param._speed);
    Debug::DrawString(anchorPos + Vector2D(130, 240), paramStr);
}


void Monster::DrawParameter(Vector2D anchorPos)
{
    const BattleParameter& param = _battleParameter;
    auto color = ColorPalette::BLUE4;

    Vector2D hpOffset(110, 130);
    Debug::DrawString(anchorPos + hpOffset, "HP");
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(param._hp / double(_maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    Vector2D mpOffset(110, 160);
    Debug::DrawString(anchorPos + mpOffset, "MP");
    Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(param._hp / double(_maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    //äÓñ{èÓïÒï`âÊ
    Character::DrawParameter(anchorPos);
}


void Enemy::DrawParameter(Vector2D anchorPos)
{
    const BattleParameter& param = _battleParameter;
    auto color = ColorPalette::RED4;

    Vector2D hpOffset(60, 130);
    Debug::DrawString(anchorPos + hpOffset, "HP");
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(param._hp / double(_maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    Vector2D mpOffset(60, 160);
    Debug::DrawString(anchorPos + mpOffset, "MP");
    Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(param._hp / double(_maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    //äÓñ{èÓïÒï`âÊ
    Character::DrawParameter(anchorPos);

    //èäéùïêäÌï\é¶
    Debug::DrawString(anchorPos + Vector2D(240, 128), "ITEM");

    if (_equipmentsGraph.HasLoaded())
        _equipmentsGraph.SetPosition(anchorPos + Vector2D(220, 148));
    else
        Debug::DrawRectWithSize(anchorPos + Vector2D(220, 148), {32.0, 32.0}, ColorPalette::BLACK4, false);

    Debug::DrawRectWithSize(anchorPos + Vector2D(260, 148), { 32.0, 32.0 }, ColorPalette::BLACK4, false);
}