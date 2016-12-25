#ifndef MouseInput_h
#define MouseInput_h

#include <unordered_map>
#include <memory>
#include "../Utility/Singleton.h"
#include "ButtonTypeInput.h"
#include "MouseTypeInputEvent.h"
#include "DxLib.h"

class MouseInput : public Singleton<MouseInput>
{
    friend class Singleton<MouseInput>;
    friend class InputManager;

public:

    enum class MouseButtonCode
    {
        MOUSE_L = 0,
        MOUSE_R,
        MOUSE_CENTER
    };

    //Eventの状態を確認するためのオブジェクト
    struct MouseEvent
    {
        MouseEvent(std::function<void(Vector2D)>* eve
            , MouseButtonCode code
            , MouseTypeInputEvent::State state)
            : _event(eve), _code(code), _state(state) {}

        const std::function<void(Vector2D)>* _event;
        const MouseButtonCode _code;
        const MouseTypeInputEvent::State _state;
    };

    //指定のボタンが各状態にあるかどうか
    bool ButtonUp(MouseButtonCode button) const { return _inputMap.at(button)->_inputData.ButtonUp(); };
    bool ButtonDown(MouseButtonCode button) const { return _inputMap.at(button)->_inputData.ButtonDown(); };
    bool ButtonBeingPressed(MouseButtonCode button) const { return _inputMap.at(button)->_inputData.ButtonBeingPressed(); };

    //左クリックがダブルクリックされたかどうか
    bool DoubleClicked() const { return _hasDoubleClicked; };

    //カーソルの座標を取得
    Vector2D GetCursorPos() const { return _cursorPos; };

    std::shared_ptr<MouseEvent> AddEvent(MouseButtonCode code, MouseTypeInputEvent::State state, std::function<void(Vector2D)> eve)
    {
        auto eventRef = GetEvent(code)->AddEvent(state, eve);
        return std::make_shared<MouseEvent>(eventRef, code, state);
    }
    void RemoveEvent(const std::shared_ptr<MouseEvent> eventRef)
    {
        GetEvent(eventRef->_code)->RemoveEvent(eventRef->_state, eventRef->_event);
    }

private:

    MouseInput();
    ~MouseInput();

    void RegistRecords();
    void Update();
    void Clear();

    ButtonTypeInput *GetButton(MouseButtonCode button) { return &_inputMap.at(button)->_inputData; }
    MouseTypeInputEvent *GetEvent(MouseButtonCode button) { return &_inputMap.at(button)->_inputEvents; }

    void UpdateDoubleClickStaet();

    struct MouseData
    {
        MouseData(MouseButtonCode code, int value)
            : _code(code)
            , _inputCode(value)
            , _inputEvents(&_inputData)
        {
        }

        //ライブラリで用意したキー入力識別の列挙型
        MouseButtonCode _code;
        //APIに用意されてるキー入力の値
        int _inputCode;
        //ボタンの入力状態
        ButtonTypeInput _inputData;
        //入力状態に基づいたイベント
        MouseTypeInputEvent _inputEvents;
    };

    void AddRecord(MouseButtonCode code, int value);
    std::unordered_map<MouseButtonCode, MouseData *> _inputMap;
    std::vector<MouseData *> _inputs;

    Vector2D _cursorPos;

    //ダブルクリック検出用
    bool _hasClicked;
    bool _hasDoubleClicked;
    int _countFromFirstClick;
};

#define MOUSE MouseInput::GetInstance()

#endif /* MouseInput_h */
