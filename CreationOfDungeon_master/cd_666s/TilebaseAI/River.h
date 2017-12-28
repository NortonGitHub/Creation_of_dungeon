#pragma once
#include "Obstacle.h"

class River : public Obstacle
{
public:
    River(TiledVector tilePos);
    ~River();

    void Init() override;
};

