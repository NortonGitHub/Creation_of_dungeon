#pragma once
#include "Trap.h"
#include "../../mw_animation/GraphArray.h"

class Enemy;

class MineBomb : public Trap
{
public:
    MineBomb(TiledVector trap, int cost, int range, int power, int attack, int stuckTime, bool mine);
    ~MineBomb();

    void Draw() override;
    void Activate() override;
    bool IsActivatable() const override;

    static std::shared_ptr<MineBomb> Create(std::string data, TiledVector pos);

private:

    // TODO : ちゃんとbareTrapとクラス分けする
    bool _isMine;
    Sound _explodeSounde;

    //爆風範囲
    int _range;

    //爆風によるダメージ
    int _power;
    int _attack;

    //硬直時間
    int _stuckedTime;

    GraphArray _graphArray;

    mutable Enemy* _targetCache;
};

