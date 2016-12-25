#pragma once
#include <functional>
#include <vector>
#include "../../Vector2D.h"
class ButtonTypeInput;

class MouseTypeInputEvent
{
    typedef std::vector<std::function<void(Vector2D)>> Events;
    typedef std::function<void(Vector2D)> Event;

public:

    enum class State
    {
        Pressing = 0,
        Down,
        Up
    };
    
    MouseTypeInputEvent(const ButtonTypeInput *button);
    ~MouseTypeInputEvent();

    void Update(Vector2D vec);
    
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

