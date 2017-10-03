#include "DungeonTimer.h"
#include "../DebugDraw.h"

DungeonTimer::DungeonTimer()
    : _count(0)
    , _waveInterval(0)
    , _halfSE("resourse/sound/time_half1.wav")
    , _littleSE("resourse/sound/time_little1.wav")
    , _endSE("resourse/sound/game_end.wav")
    , _clock("resourse/graph/ui/ClockDaytime.png")
    , _hand("resourse/graph/ui/ClockHand.png")
    , _position(754, 248)
{
    _halfSE.SetVolume(200);
    _littleSE.SetVolume(200);
    _endSE.SetVolume(200);

    _clock.SetPosition(Vector2D::zero);
    _clock.SetRenderType(Texture2D::RenderType::UI);

    _hand.SetPosition(Vector2D::zero);
    _hand.SetRenderType(Texture2D::RenderType::UI);
    _hand.GetTexturePtr().lock()->SetAnchorType(Texture2D::AnchorType::UPPER_LEFT);
}


DungeonTimer::~DungeonTimer()
{
}


void DungeonTimer::InitWithSetup(long waveTime)
{
    _count = 0;

    _waveInterval = waveTime;

    //ゲーム時間換算で秒単位に変換
    _waveInterval *= 60;

    _hand.Rotate(80);
}


void DungeonTimer::Update()
{
    //時間になったら初期化
    if (_waveInterval < _count)
    {
        return;
    }
    else
    {
        _count++;
    }

    auto timeRatio = GetTimeRatio();

    if (timeRatio == 0.5)
    {
        if (!_halfSE.IsPlaying())
            _halfSE.Play();

        return;
    }
   
    if (timeRatio == 0.8)
    {
        if (!_littleSE.IsPlaying())
            _littleSE.Play();

        return;
    }

    if (timeRatio == 1.0)
    {
        if (!_endSE.IsPlaying())
            _endSE.Play();

        return;
    }
}


void DungeonTimer::Draw()
{
    //残り時間デバッグ表示
    std::string timerStr = "Time:";
    Debug::DrawString(_position + Vector2D(20, 20), timerStr);
    timerStr = std::to_string((_waveInterval - _count) / 60);
    timerStr += "/";
    timerStr += std::to_string(_waveInterval / 60);
    Debug::DrawString(_position + Vector2D(40, 40), timerStr);

    auto offset = 10;
    auto timeRatio = static_cast<double>(_count - _waveInterval) / static_cast<double>(_waveInterval);
    _hand.Rotate(timeRatio * (90 - offset));
}