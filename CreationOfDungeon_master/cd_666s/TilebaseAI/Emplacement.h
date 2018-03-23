#pragma once
#include "Trap.h"
#include "../../mw_animation/GraphArray.h"

class Enemy;

class Emplacement : public Trap
{
public:
    Emplacement(TiledVector pos, int cost, int power, int attack, TiledVector::Direction direction);
    ~Emplacement();

    void Activate() override;
    bool IsActivatable() const override;
    bool Contain(Vector2D pos) const override;

	bool IsOverwritable(TiledObject* overwriter) override;

    static std::shared_ptr<Emplacement> Create(std::string data, TiledVector pos);

private:

    //UŒ‚—Í
    int _attack;

    //ˆĞ—Í
    int _power;

    //UŒ‚•ûŒü
    TiledVector::Direction _shootDirection;

    //UŒ‚•ûŒü‚É‘Î‰‚µ‚½‰æ‘œ
    //GraphArray _directedGraph;

    //‘Å‚¿o‚·‚à‚Ì‚Ì‰æ‘œ
    std::shared_ptr<ImageResource> _bulletImage;
};

