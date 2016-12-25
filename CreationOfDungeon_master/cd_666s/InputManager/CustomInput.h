#ifndef CustomInpur_h
#define CustomInpur_h
#include <unordered_map>
#include "../Utility/Singleton.h"
#include "ButtonInputData.h"
#include "KeyInput.h"
#include "ButtonTypeInput.h"
#include "ButtonTypeInputEvent.h"


class CustomInput : public Singleton<CustomInput>
{
    friend class Singleton<CustomInput>;
    friend class InputManager;
    
public:
    
    enum class CustomInputType
    {
        BUTTON0 = 0,
        BUTTON1,
        BUTTON2,
        BUTTON3,
        BUTTON4,
        BUTTON5,
        BUTTON6,
        BUTTON7,
        BUTTON8,
        BUTTON9
    };

    //Eventの状態を確認するためのオブジェクト
    struct CustomInputEvent
    {
        CustomInputEvent(std::function<void()>* eve
            , CustomInputType code
            , ButtonTypeInputEvent::State state)
            : _event(eve), _code(code), _state(state) {}

        const std::function<void()>* _event;
        const CustomInputType _code;
        const ButtonTypeInputEvent::State _state;
    };

    bool ButtonUp(CustomInputType type) const { return _inputMap.at(type)->_origin->_inputData.ButtonUp(); };
    bool ButtonDown(CustomInputType type) const { return _inputMap.at(type)->_origin->_inputData.ButtonDown(); };
    bool ButtonBeingPressed(CustomInputType type) const { return _inputMap.at(type)->_origin->_inputData.ButtonBeingPressed(); };

    std::shared_ptr<CustomInputEvent> AddEvent(CustomInputType type, ButtonTypeInputEvent::State state, std::function<void()> eve)
    {
        auto eventRef = GetEvent(type)->AddEvent(state, eve);
        return std::make_shared<CustomInputEvent>(eventRef, type, state);
    }

    void RemoveEvent(const std::shared_ptr<CustomInputEvent> eventRef)
    {
        GetEvent(eventRef->_code)->RemoveEvent(eventRef->_state, eventRef->_event);
    }

    void ReplaceButtonCode(CustomInputType input, KeyInput::KeyType key);

private:

    CustomInput();
    ~CustomInput();

    void RegistRecords();
    void Clear();

    ButtonTypeInput *GetCustomButtob(CustomInputType type) { return &_inputMap.at(type)->_origin->_inputData; }
    ButtonTypeInputEvent *GetEvent(CustomInputType type) { return &_inputMap.at(type)->_origin->_inputEvents; }


    class CustomInputData
    {
    public:
        CustomInputData(CustomInputType type, ButtonInputData *data)
            : _origin(data)
            , _type(type)
        {
        }

        //ライブラリで用意したキー入力識別の列挙型
        CustomInputType _type;
        //
        ButtonInputData *_origin;
    };

    void AddRecord(CustomInputType type, ButtonInputData* data);
    std::unordered_map<CustomInputType, CustomInputData *> _inputMap;
    std::vector<CustomInputData *> _usingInputs;
};

#define CUSTOM_INPUT CustomInput::GetInstance()

#endif /* CustomInpur_h */
