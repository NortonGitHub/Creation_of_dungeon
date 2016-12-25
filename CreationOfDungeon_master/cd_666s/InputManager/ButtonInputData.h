#ifndef ButtonInputData_h
#define ButtonInputData_h

#include "ButtonTypeInput.h"
#include "ButtonTypeInputEvent.h"


struct ButtonInputData
{
    ButtonInputData(int value)
    : _inputCode(value)
    , _inputEvents(&_inputData)
    {
    }
    
    //APIに用意されてるキー入力の値
    int _inputCode;
    //ボタンの入力状態
    ButtonTypeInput _inputData;
    //入力状態に基づいたイベント
    ButtonTypeInputEvent _inputEvents;
};

#endif /* ButtonInputData_h */
