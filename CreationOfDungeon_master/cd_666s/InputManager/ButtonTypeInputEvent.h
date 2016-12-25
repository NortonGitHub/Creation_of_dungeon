#pragma once
#include <functional>
#include <vector>

class ButtonTypeInput;

class ButtonTypeInputEvent
{
    typedef std::function<void()> Event;
    typedef std::vector<std::function<void()>> Events;

public:

    enum class State
    {
        Pressing = 0,
        Down,
        Up
    };

    ButtonTypeInputEvent(const ButtonTypeInput *button);
    ~ButtonTypeInputEvent();

    void Update();

    void ClearEventsAll();
    void ClearEvents(State state);

    Event* AddEvent(State state, Event buttonEvent);
    void RemoveEvent(const State state, const Event* buttonEventPtr);

private:
    const ButtonTypeInput *_button;

    Events _onButtonPressing;
    Events _onButtonDown;
    Events _onButtonUp;
};

