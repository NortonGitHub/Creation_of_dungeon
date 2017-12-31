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
    , _enemyThumbnail("resource/graph/ui/StatusWindow.png", position)
    , _allyThumbnail("resource/graph/ui/StatusWindowBlue.png", position)
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
    _icon->SetPosition(_position + Vector2D(30, 30));
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

	DrawAffectedParameter("ATK : ", param._attack, rawParam._attack, anchorPos + Vector2D(106, 135));	//barsize 157,14
	DrawAffectedParameter("DEF : ", param._defence, rawParam._defence, anchorPos + Vector2D(106, 166));
	DrawAffectedParameter("MATK : ", param._magicAttack, rawParam._magicAttack, anchorPos + Vector2D(106, 197));
	DrawAffectedParameter("MDEF : ", param._magicDefence, rawParam._magicDefence, anchorPos + Vector2D(106, 231));
	//DrawAffectedParameter("SPD : ", param._speed, rawParam._speed, anchorPos + Vector2D(240, 190));

	std::string LevelText = "";

	if (GetLevel() < 0) {
		LevelText = "";
	}
	else {
		LevelText = " Lv" + std::to_string(GetLevel());
	}

	Debug::DrawString(anchorPos + Vector2D(129, 75), GetName() + LevelText, ColorPalette::BLACK4, 32);

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
    auto hpcolor = ColorPalette::RED4;
	auto mpcolor = ColorPalette::GREEN4;

    Vector2D hpOffset(123, 16);
    Debug::DrawRectWithSize(anchorPos + hpOffset, Vector2D(param._hp / double(param._maxHP) * 200, 30), hpcolor, true);

    Vector2D mpOffset(15, 253);
	if (_skill != nullptr)
	{
		auto height = -(_skill->_mp / double(_skill->_mpCost) * 130);
		Debug::DrawRectWithSize(anchorPos + mpOffset, Vector2D(30, height), mpcolor, true);
	}

    //基本情報描画
    Character::DrawParameter(anchorPos);
}


void Enemy::DrawParameter(Vector2D anchorPos)
{
    const BattleParameter param = GetAffectedParameter();
	auto hpcolor = ColorPalette::RED4;
	auto mpcolor = ColorPalette::GREEN4;

	Vector2D hpOffset(123, 16);
	Debug::DrawRectWithSize(anchorPos + hpOffset, Vector2D(param._hp / double(param._maxHP) * 200, 30), hpcolor, true);

	Vector2D mpOffset(15, 253);
    //Debug::DrawString(anchorPos + mpOffset, "MP");
    if (_skill != nullptr)
    {
		auto height = -(_skill->_mp / double(_skill->_mpCost) * 130);
        Debug::DrawRectWithSize(anchorPos + mpOffset, Vector2D(30, height), mpcolor, true);
    }

    //基本情報描画
    Character::DrawParameter(anchorPos);

    //所持武器表示
    //Debug::DrawString(anchorPos + Vector2D(230, 128), "ITEM");

    if (_equipmentsGraph.HasLoaded())
        _equipmentsGraph.SetPosition(anchorPos + Vector2D(200, 148));

    for (size_t i=0; i<_consumableItems.size(); ++i)
    {
		Vector2D pos = Vector2D(284, 126 + i * 32 + 8 * i);
        if (_consumableItemGraphs[i].HasLoaded())
            _consumableItemGraphs[i].SetPosition(anchorPos + pos);
    }
}


void DrawAffectedParameter(std::string paramName, int affectedParam, int rawParam, Vector2D anchorPos)
{
	const Vector2D max_bar_size(157, 14);
	auto ratio = max_bar_size._x / 100;
	auto bar_size = max_bar_size;
	bar_size._x = affectedParam * ratio;

	Color4 color = ColorPalette::LIGHTBLUE4;

	if (affectedParam != rawParam)
	{
		//値が初期値から変わっていたら色付きで出力
		color = (affectedParam < rawParam) ? ColorPalette::PURPLE4 : ColorPalette::ORANGE4;
	}
	Debug::DrawRectWithSize(anchorPos, bar_size, color, true);
}