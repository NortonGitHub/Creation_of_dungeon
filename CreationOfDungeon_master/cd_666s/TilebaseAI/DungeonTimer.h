#pragma once
#include "../Render/Sprite.h"
#include "../Sound/Sound.h"
#include "../../Vector2D.h"

class DungeonTimer
{
public:

    DungeonTimer();
    ~DungeonTimer();

    void Update();
    void Draw();

    void InitWithSetup(long waveTime);

    long GetWaveInterval() const { return _waveInterval; };
    long GetCount() const { return _count; };

    bool HasTimeUp() const { return (_waveInterval < _count); }

    double GetTimeRatio() const { return static_cast<double>(_count) / _waveInterval; }

private:

    long _count;
    long _waveInterval;

    Vector2D _position;
    Sound _halfSE, _littleSE, _endSE;
    Sprite _clock, _hand;
};