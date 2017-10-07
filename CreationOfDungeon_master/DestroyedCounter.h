#pragma once
#include "./cd_666s/Render/Sprite.h"
#include "./cd_666s/Sound/Sound.h"
#include "./Vector2D.h"

class DestroyedCounter
{
public:
	DestroyedCounter();
	~DestroyedCounter();

	void Update(int count);
	void Draw();

	void Init();

	void InitWithSetup(int leftEnemy);

	int GetAllEnemy() const { return _all_enemy; }
	int GetCount() const { return _count; }

	bool HasDestroyedAll() const { return (_all_enemy < _count); }

	double GetCountRatio() const { return static_cast<double>(_count) / _all_enemy; }

private:
	int _count;
	int _all_enemy;

	Vector2D _position;
	Sprite _clock, _hand;

};

