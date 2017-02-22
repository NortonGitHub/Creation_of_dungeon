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
    const BattleParameter& param = GetAffectedParameter();

    std::string paramStr = "ATK : ";
    paramStr += std::to_string(param._attack);
    Debug::DrawString(anchorPos + Vector2D(40, 190), paramStr);

    paramStr = "DEF : ";
    paramStr += std::to_string(param._defence);
    Debug::DrawString(anchorPos + Vector2D(140, 190), paramStr);

    paramStr = "MATK : ";
    paramStr += std::to_string(param._magicAttack);
    Debug::DrawString(anchorPos + Vector2D(40, 215), paramStr);

    paramStr = "MDEF : ";
    paramStr += std::to_string(param._magicDefence);
    Debug::DrawString(anchorPos + Vector2D(140, 215), paramStr);

    paramStr = "SPD : ";
    paramStr += std::to_string(param._speed);
    Debug::DrawString(anchorPos + Vector2D(240, 190), paramStr);

    size_t enableCount = 0;
    for (size_t i = 0; i < _effecters.size(); ++i)
    {
        if (!_effecters[i]->IsEnable())
            continue;

        Vector2D anchor = anchorPos + Vector2D(90 + i * 40, 250);
        _effecters[i]->DrawEffecter(anchor);
        enableCount++;
    }
}


void Monster::DrawParameter(Vector2D anchorPos)
{
    const BattleParameter param = GetAffectedParameter();
    auto color = ColorPalette::BLUE4;

    Vector2D hpOffset(110, 130);
    Debug::DrawString(anchorPos + hpOffset, "HP");
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(param._hp / double(param._maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    Vector2D mpOffset(110, 160);
    Debug::DrawString(anchorPos + mpOffset, "MP");
    if (_skill != nullptr)
    {
        Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(_skill->_mp / double(_skill->_mpCost) * 96, 12), color, true);
        Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);
    }
    else
    {
        Debug::DrawString(anchorPos + mpOffset + Vector2D(24, 0), "�X�L���Ȃ�");
    }
    //��{���`��
    Character::DrawParameter(anchorPos);
}


void Enemy::DrawParameter(Vector2D anchorPos)
{
    const BattleParameter param = GetAffectedParameter();
    auto color = ColorPalette::RED4;

    Vector2D hpOffset(60, 130);
    Debug::DrawString(anchorPos + hpOffset, "HP");
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(param._hp / double(param._maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(anchorPos + hpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    Vector2D mpOffset(60, 160);
    Debug::DrawString(anchorPos + mpOffset, "MP");
    if (_skill != nullptr)
    {
        Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(_skill->_mp / double(_skill->_mpCost) * 96, 12), color, true);
        Debug::DrawRectWithSize(anchorPos + mpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);
    }
    else
    {
        Debug::DrawString(anchorPos + mpOffset + Vector2D(24, 0), "�X�L���Ȃ�");
    }
    //��{���`��
    Character::DrawParameter(anchorPos);

    //��������\��
    Debug::DrawString(anchorPos + Vector2D(230, 128), "ITEM");

    if (_equipmentsGraph.HasLoaded())
        _equipmentsGraph.SetPosition(anchorPos + Vector2D(200, 148));
    else
        Debug::DrawRectWithSize(anchorPos + Vector2D(200, 148), {32.0, 32.0}, ColorPalette::BLACK4, false);

    for (size_t i=0; i<_consumableItems.size(); ++i)
    {
        if (_consumableItemGraphs[i].HasLoaded())
            _consumableItemGraphs[i].SetPosition(anchorPos + Vector2D(234 + i * 32 + 2 * i, 148));
        else
            Debug::DrawRectWithSize(anchorPos + Vector2D(234 + i * 32 + 2 * i, 148), { 32.0, 32.0 }, ColorPalette::BLACK4, false);
    }

    //Debug::DrawRectWithSize(anchorPos + Vector2D(260, 148), { 32.0, 32.0 }, ColorPalette::BLACK4, false);
}