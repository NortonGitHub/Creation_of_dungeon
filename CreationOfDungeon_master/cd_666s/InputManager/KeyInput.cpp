#include "KeyInput.h"
#include "DxLib.h"

KeyInput::KeyInput()
{
    RegistRecords();
}



KeyInput::~KeyInput()
{
    Clear();
}


void KeyInput::RegistRecords()
{
    AddRecord(KeyType::KEY_Z, KEY_INPUT_Z);
    AddRecord(KeyType::KEY_X, KEY_INPUT_X);
    AddRecord(KeyType::KEY_C, KEY_INPUT_C);
    AddRecord(KeyType::KEY_V, KEY_INPUT_V);
    AddRecord(KeyType::KEY_LSHIHT, KEY_INPUT_LSHIFT);
    AddRecord(KeyType::KEY_SPACE, KEY_INPUT_SPACE);
    AddRecord(KeyType::KEY_ARROW_LEFT, KEY_INPUT_LEFT);
    AddRecord(KeyType::KEY_ARROW_RIGHT, KEY_INPUT_RIGHT);
    AddRecord(KeyType::KEY_ARROW_UP, KEY_INPUT_UP);
    AddRecord(KeyType::KEY_ARROW_DOWN, KEY_INPUT_DOWN);
    AddRecord(KeyType::KEY_ESCAPE, KEY_INPUT_ESCAPE);
}


void KeyInput::AddRecord(KeyType type, int value)
{
    auto *data = new KeyInputData(type, value);
    _inputMap.insert(std::make_pair(type, data));
    _usingInputs.push_back(data);
}


void KeyInput::Update()
{
    for (auto input : _usingInputs)
    {
        //押されているかどうかをもとに状態更新
        ButtonTypeInput &data = input->_inputData;
        data.UpdateState(CheckHitKey(input->_inputCode) == 1);
        
        //状態をもとにイベントを駆動させる
        ButtonTypeInputEvent &events = input->_inputEvents;
        events.Update();
    }
}


void KeyInput::Clear()
{
    for (auto input : _usingInputs)
    {
        ButtonTypeInputEvent &events = input->_inputEvents;
        events.ClearEventsAll();
    }
}


KeyInput::KeyType KeyInput::GetInputedType() const
{
    for (auto input : _usingInputs)
    {
        if (input->_inputData.ButtonDown())
            return input->_type;
    }
    
    return KeyType::NONE;
}


int KeyInput::GetInputedCode() const
{
    for (auto input : _usingInputs)
    {
        if (input->_inputData.ButtonDown())
            return input->_inputCode;
    }
    
    return 0;
}


int KeyInput::GetCodeOfType(KeyType type) const
{
    for (auto input : _usingInputs)
    {
        if (input->_type == type)
            return input->_inputCode;
    }
    
    return 0;
}