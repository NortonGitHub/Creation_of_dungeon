#pragma once
#include "cd_666s/TilebaseAI/GraphicalObject.h"
#include "mw_animation/Animator.h"

class Character;

class BossBattleObject :
	public GraphicalObject
{
public:
	BossBattleObject();
	BossBattleObject(Vector2D pos, std::string name);
	~BossBattleObject();

	enum class Type
	{
		DEFAULT,
		BOSS,
		ENEMY,
		FACE
	};

	//ループ処理の前に1度だけ呼ばれる処理
	virtual void Init();

	virtual void Update() override;
	virtual void Draw() override;

	//能動動作できるオブジェクトから呼び出される関数
	virtual void Interact(Character& character);

	//アイテム取得での消失や召喚されたかどうかなど、
	//オブジェクトは生成しても判定に用いるかどうかを判断するのに用いる.
	//詳細な条件は派生先によって異なる.
	virtual bool IsEnable() const { return true; }

	//オブジェクトが倒されたことを示すときに使用
	virtual int GetDefeatedNum() const { return 0; }

	//オブジェクトが目的地にたどり着いたかどうかを返す
	virtual bool HasArrived() const { return true; }

	Type GetType() const { return _type; }

protected:

	std::string _name;
	Type _type;

	//自分がボス部屋の中にいるか
	bool _isInRoom;

	Animator _animator;

private:
	Vector2D _position;
};

