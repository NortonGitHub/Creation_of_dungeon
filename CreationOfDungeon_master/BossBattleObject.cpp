#include "BossBattleObject.h"



BossBattleObject::BossBattleObject()
{
}

BossBattleObject::BossBattleObject(Vector2D pos, std::string name)
	: _type(Type::DEFAULT)
{
	_position = pos;
	std::string fileName = "resource/graph/bossbattle/";
	fileName += name;
	_animator.AddAnimation("wait", std::make_shared<GraphArray>(fileName + "wait", 32, 24));
	_animator.AddAnimation("attack", std::make_shared<GraphArray>(fileName + "wait", 32, 24));

	auto currentGraph = _animator.GetCurrentGraph();
	currentGraph->SetDisplayMode(false);
	_animator.Transform([&](GraphArray* animation)
	{
		animation->GetGraphPtr()->SetPosition(_position);
		//animation->GetGraphPtr()->SetScale(Vector2D(TILE_SCALE, TILE_SCALE));
		animation->GetGraphPtr()->SetRenderType(Texture2D::RenderType::UI);
	});
}


BossBattleObject::~BossBattleObject()
{
}

void BossBattleObject::Init()
{
	_graph.SetScale(Vector2D(1.0 ,1.0));
}

void BossBattleObject::Update()
{
	GraphicalObject::Update();

	if (!_isInRoom)
		return;

	//Žp¨î•ñXV
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
}

void BossBattleObject::Interact(Character & character)
{
}

