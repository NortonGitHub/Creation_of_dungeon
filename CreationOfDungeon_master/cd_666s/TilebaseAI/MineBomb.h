#pragma once
#include "Trap.h"
#include "../../mw_animation/GraphArray.h"

class MineBomb : public Trap
{
public:
    MineBomb(TiledVector trap);
    ~MineBomb();

    void Update() override;
    void Draw() override;
    bool IsEnable() const override;

private:

    //”š•—”ÍˆÍ
    int _range;

    //”š•—‚É‚æ‚éƒ_ƒ[ƒW
    int _damage;

    GraphArray _graphArray;
};

