#pragma once
#include "Obstacle.h"

class River : public Obstacle
{
private:
	std::string typeText;

public:
    River(TiledVector tilePos);
	River(TiledVector tilePos, std::string typeText);
    ~River();

    void Init() override;

	bool IsOverwritable(TiledObject* overwriter) override;
};

