#pragma once
#include "TiledObject.h"

class Obstacle : public TiledObject
{
public:
    Obstacle(TiledVector tilePos);
    virtual ~Obstacle();

    bool IsOverwritable(TiledObject* overwriter) override;

    virtual void Init() override;
    void Update() override;
    void Draw() override;

private:
    std::string GetNameFromAroundInfo(TiledVector tilePos);
};

