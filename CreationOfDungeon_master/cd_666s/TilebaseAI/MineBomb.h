#pragma once
#include "Trap.h"
#include "../../mw_animation/GraphArray.h"

class Enemy;

class MineBomb : public Trap
{
public:
    MineBomb(TiledVector trap);
    ~MineBomb();

    void Update() override;
    void Draw() override;
	void Activate() override;

    bool IsEnable() const override;
	bool IsActivatable() const override;

private:

    //”š•—”ÍˆÍ
    int _range;

    //”š•—‚É‚æ‚éƒ_ƒ[ƒW
    int _damage;

    GraphArray _graphArray;

	mutable Enemy* _targetCache;
};

