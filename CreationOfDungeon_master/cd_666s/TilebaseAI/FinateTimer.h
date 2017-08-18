#pragma once
class FinateTimer
{
public:
    FinateTimer(int interval, bool countOnStart, bool isLoop);
    ~FinateTimer();

    void ResetCount(bool withStop = false);
    void Reset(int interval, bool countOnStart, bool isLoop);
    void Play();
    void Stop();
    void Update();

    bool IsCounting() const { return _isCounting; }
    bool CountOnZero() const { return _count == 0; }
    bool CountOnEnd() const { return _count == _interval; }
    int GetCount() const { return _count; }
    int GetInterval() const { return _interval; }

private:

    int _count;
    int _interval;

    //タイマーが稼働してるか
    bool _isCounting;

    //intervalに到達したあと停止するか
    bool _loop;
};

