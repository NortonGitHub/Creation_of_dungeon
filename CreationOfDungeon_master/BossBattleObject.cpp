#include "BossBattleObject.h"
#include "cd_666s/TilebaseAI/TiledObjectMnager.h"
#include "cd_666s/TilebaseAI/TiledVector.h"
#include "cd_666s/TilebaseAI/ColleagueNotifyer.h"

BossBattleObject::BossBattleObject(Vector2D startPos, BattleParameter param, ColleagueNotifyer& notifyer, std::string name, bool _isBoss)
	: Character(TiledVector::ConvertToTiledPos(startPos), param, notifyer , name, TiledObject::Type::BOSS_SCENE, _isBoss)
	, _isInRoom(false)
	, move_sum(0.0)
{
	_position = startPos;
	_appearSE.Load("resource/sound/blockSelect.wav");
	
	_direction = TiledVector::Direction::LEFT;
	_animator.SwitchWithReset("left");

	_param = param;

#if 0
	std::string fileName = "resource/graph/tiledObject/";

	fileName += name;

	int _graphSize = 64;
	if (name.find("boss") == std::string::npos) {
		_objType = ObjectType::ENEMY;
		fileName += "_left";
		_graphSize = 32;
	}
	else {
		fileName += "_right";
	}

	_animator.AddAnimation("", std::make_shared<GraphArray>(fileName + ".png", _graphSize, 24));

	auto currentGraph = _animator.GetCurrentGraph();
	currentGraph->SetDisplayMode(false);
	_animator.Transform([&](GraphArray* animation)
	{
		animation->GetGraphPtr()->SetPosition(_position);
		//animation->GetGraphPtr()->SetScale(Vector2D(TILE_SCALE, TILE_SCALE));
		animation->GetGraphPtr()->SetRenderType(Texture2D::RenderType::UI);
	});
#endif
}

BossBattleObject::~BossBattleObject()
{
}

void BossBattleObject::Init()
{
}

void BossBattleObject::Update()
{

	GraphicalObject::Update();

	if (!_isInRoom)
		return;


	//姿勢情報更新
	_animator.Transform([&](GraphArray* animation)
	{
		animation->GetGraphPtr()->SetPosition(_position);
	});
}

void BossBattleObject::Draw()
{
	auto currentGraph = _animator.GetCurrentGraph();
	currentGraph->SetDisplayMode(_isInRoom);

	if (!_isInRoom)
		return;

	_animator.Update();

	/*以下、ボスのHP表示(Debug仕様)*/
	if (Character::GetName().find("boss") == std::string::npos)
		return;

	const int height = 20;
	auto _pos = Vector2D(_position._x, _position._y - 30);
	auto _wh1 = Vector2D(_param._hp, height);
	auto _wh2 = Vector2D(_param._maxHP, height);

	Debug::DrawRectWithSize(_pos, _wh1, ColorPalette::RED4, true);
	Debug::DrawRectWithSize(_pos, _wh2, ColorPalette::RED4, false);
}

void BossBattleObject::Clear()
{
	_notifyer.NotifyRemoveTarget(*this);
}

void BossBattleObject::SwitchAnime(bool _isAnimate)
{
	_animator.GetCurrentAnimation()->_isLoop = _isAnimate;
	if (!_isAnimate) {
		_animator.GetCurrentAnimation()->SetIndex(0);
	}
}

void BossBattleObject::OutBossRoom()
{
	_isInRoom = false;
	SwitchAnime(false);
}
