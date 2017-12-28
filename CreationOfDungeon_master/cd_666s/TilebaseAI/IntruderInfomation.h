#pragma once
#include <vector>
#include "TiledObjectDictionary.h"
#include "../Render/Sprite.h"

class StartPoint;

class IntruderInfomation
{
public:
    IntruderInfomation(const TiledObjectDictionary& dictionary);
    ~IntruderInfomation();

    void InitWithSetup(const std::weak_ptr<StartPoint>& intrudePoint);
    void Update();
    void Draw();

private:
	long _count;
	long _waveInterval;

    Vector2D _position;
    std::weak_ptr<StartPoint> _intrudePoint;

    std::unique_ptr<Sprite> _icon;
    const TiledObjectDictionary& _dictionary;

	Sprite _hand;
	int startTime;
};

