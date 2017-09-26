#include "TiledObjectInformation.h"
#include "ObjectInformationDrawer.h"
#include "Character.h"
#include "Monster.h"
#include "Enemy.h"
#include "../DebugDraw.h"
#include "../Color.h"

void DrawAffectedParameter(std::string paramName, int affectedParam, int rawParam, Vector2D anchorPos);

TiledObjectInformation::TiledObjectInformation(const TiledObjectDictionary& iconDictionary, Vector2D position)
    : _position(position)
    , _character(nullptr)
    , _iconDictionary(iconDictionary)
    , _enemyThumbnail("resource/graph/enemy_thumbnail.png", position)
    , _allyThumbnail("resource/graph/ally_thumbnail.png", position)
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
	const BattleParameter& rawParam = GetRawParameter();

	DrawAffectedParameter("ATK : ", param._attack, rawParam._attack, anchorPos + Vector2D(40, 190));
	DrawAffectedParameter("DEF : ", param._defence, rawParam._defence, anchorPos + Vector2D(140, 190));
	DrawAffectedParameter("MATK : ", param._magicAttack, rawParam._magicAttack, anchorPos + Vector2D(40, 215));
	DrawAffectedParameter("MDEF : ", param._magicDefence, rawParam._magicDefence, anchorPos + Vector2D(140, 215));
	DrawAffectedParameter("SPD : ", param._speed, rawParam._speed, anchorPos + Vector2D(240, 190));

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
        Debug::DrawString(anchorPos + mpOffset + Vector2D(24, 0), "スキルなし");
    }

    //基本情報描画
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
        Debug::DrawString(anchorPos + mpOffset + Vector2D(24, 0), "スキルなし");
    }
    //基本情報描画
    Character::DrawParameter(anchorPos);

    //所持武器表示
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
}


void DrawAffectedParameter(std::string paramName, int affectedParam, int rawParam, Vector2D anchorPos)
{
	paramName += std::to_string(affectedParam);

	if (affectedParam == rawParam)
	{
		Debug::DrawString(anchorPos, paramName);
		return;
	}

	//値が初期値から変わっていたら色付きで出力
	auto color = (affectedParam < rawParam) ? ColorPalette::BLUE4 : ColorPalette::RED4;
	Debug::DrawString(anchorPos, paramName, color);
}