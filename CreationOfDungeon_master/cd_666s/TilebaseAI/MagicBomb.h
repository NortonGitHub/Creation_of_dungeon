#pragma once
#include "Trap.h"
#include "../../mw_animation/GraphArray.h"

class MagicBomb : public Trap
{
public:
    MagicBomb(TiledVector trap, int cost, int range, int power, int attack);
    ~MagicBomb();

    void Activate() override;
    bool IsActivatable() const override;

private:

    //�����͈�
    int _range;

    //�����ɂ��_���[�W
    int _power;
    int _attack;

    GraphArray _graphArray;
};

