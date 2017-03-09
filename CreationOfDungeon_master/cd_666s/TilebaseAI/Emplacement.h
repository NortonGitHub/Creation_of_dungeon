#pragma once
#include "Trap.h"

class Enemy;

class Emplacement : public Trap
{
public:
    Emplacement(TiledVector pos, int cost, int power, int attack, TiledVector::Direction direction);
    ~Emplacement();

    void Activate() override;
    bool IsActivatable() const override;

    static std::shared_ptr<Emplacement> Create(std::string data, TiledVector pos);

private:

    //UŒ‚—Í
    int _attack;

    //ˆĞ—Í
    int _power;

    //UŒ‚•ûŒü
    TiledVector::Direction _shootDirection;
};

