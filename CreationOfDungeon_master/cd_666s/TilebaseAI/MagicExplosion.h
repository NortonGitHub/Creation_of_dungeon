#pragma once
#include "TiledObject.h"
#include "GraphicalObject.h"
#include "../../mw_animation/GraphArray.h"

class MagicExplosion : public TiledObject
//class MagicExplosion : public GraphicalObject
{
public:
    MagicExplosion(int power, int attack, int range, TiledVector pos, TiledObject::Type type);
    ~MagicExplosion();

    void Update() override;
    void Draw() override {};
    bool IsOverwritable(TiledObject* overwriter) override { return true; }

private:

    //“G‚Éƒqƒbƒg‚µ‚½‚©
    void CheckHit();

    int _magicAttack;
    int _power;
    int _range;

    TiledObject::Type _shooterType;

    GraphArray _animation;

    bool _hasJudged;
};

