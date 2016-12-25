#pragma once
#include "TiledObject.h"

class Obstacle : public TiledObject
{
public:
    Obstacle(TiledVector tilePos);
    ~Obstacle();

    bool IsOverwritable(TiledObject* overwriter) override;

    void Init() override;
    void Update() override;
    void Draw() override;
};

