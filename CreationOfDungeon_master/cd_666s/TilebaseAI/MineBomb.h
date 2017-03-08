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

    //�����͈�
    int _range;

    //�����ɂ��_���[�W
    int _damage;

    GraphArray _graphArray;

	mutable Enemy* _targetCache;
};

