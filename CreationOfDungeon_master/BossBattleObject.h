#pragma once
#include "cd_666s/TilebaseAI/Character.h"
#include "cd_666s/DebugDraw.h"

class BossBattleObject : public Character
{
public:
	BossBattleObject(Vector2D startPos, BattleParameter param, ColleagueNotifyer & notifyer, std::string name, bool _isBoss);
	~BossBattleObject();

	enum class ObjectType
	{
		DEFAULT,
		BOSS,
		ENEMY
	};

	enum class Action
	{
		READY,
		ATTACK,
		END
	};

	//ループ処理の前に1度だけ呼ばれる処理
	void Init();

	void Update() override;
	void Draw() override;

	void Clear();

	void Think() override {};
	void Act() override {};
	bool IsOverwritable(TiledObject* overwriter) override { return false; }

	//アニメーションの開始/停止
	void SwitchAnime(bool _isAnimate);

	void OutBossRoom();

	//オブジェクトが倒されたことを示すときに使用
	virtual int GetDefeatedNum() const { return 0; }

	//ボス部屋に居る状態を変更する
	void SetInRoom(bool _inRoom) { _isInRoom =  _inRoom; }

	ObjectType GetObjectType() const { return _objType; }

	BattleParameter _param;

protected:

	ObjectType _objType;
	Action _action;		//行動の内容

	//自分がボス部屋の中にいるか
	bool _isInRoom;

	
private:
	Vector2D _position;
	double move_sum;
};

