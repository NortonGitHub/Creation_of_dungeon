#pragma once

#include "TiledObject.h"

class WeakObstacle : public TiledObject
{
public:
    WeakObstacle(TiledVector tilePos);
    virtual ~WeakObstacle();

    bool IsOverwritable(TiledObject* overwriter) override;

    virtual void Init() override;
    void Update() override;
    void Draw() override;

private:
    std::string GetNameFromAroundInfo(TiledVector tilePos);
};

