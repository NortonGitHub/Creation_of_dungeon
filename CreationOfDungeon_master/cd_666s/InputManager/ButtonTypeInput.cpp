#include "ButtonTypeInput.h"


ButtonTypeInput::ButtonTypeInput()
{
    _inputingFrame = 0;
    _isPressing = false;
    _beforeFramePressed = false;
}


ButtonTypeInput::~ButtonTypeInput()
{
}


void ButtonTypeInput::UpdateState(bool state)
{
    _beforeFramePressed = _isPressing;

    if (state)
    {
        _inputingFrame++;
        _isPressing = true;
    }
    else
    {
        _inputingFrame = 0;
        _isPressing = false;
    }
}