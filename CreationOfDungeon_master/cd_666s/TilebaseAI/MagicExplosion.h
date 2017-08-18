#pragma once
#include "TiledObject.h"
#include "../Resources/ImageResource.h"
#include "../Sound/Sound.h"
#include "../../mw_animation/GraphArray.h"

class MagicExplosion : public TiledObject
{
public:
    MagicExplosion(int power, int attack, int range, TiledVector pos, TiledObject::Type type, std::shared_ptr<ImageResource> image);
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

    Sound _sound;
    GraphArray _animation;

    bool _hasJudged;
};

