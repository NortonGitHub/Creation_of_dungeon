#ifndef KeyInput_h
#define KeyInput_h

#include <unordered_map>
#include <memory>
#include "../Utility/Singleton.h"
#include "ButtonInputData.h"

class KeyInput : public Singleton<KeyInput>
{
    friend class Singleton<KeyInput>;
    friend class InputManager;

public:

    enum class KeyType
    {
        KEY_Z = 0,
        KEY_X,
        KEY_C,
        KEY_V,
        KEY_LSHIHT,
        KEY_SPACE,
        KEY_ARROW_LEFT,
        KEY_ARROW_RIGHT,
        KEY_ARROW_UP,
        KEY_ARROW_DOWN,

        NONE
    };

    //Eventの状態を確認するためのオブジェクト
    struct KeyEvent
    {
        KeyEvent(std::function<void()>* eve
            , KeyType key
            , ButtonTypeInputEvent::State state)
            : _event(eve), _key(key), _state(state) {}

        const std::function<void()>* _event;
        const KeyType _key;
        const ButtonTypeInputEvent::State _state;
    };

    bool ButtonUp(KeyType key) const { return _inputMap.at(key)->_inputData.ButtonUp(); };
    bool ButtonDown(KeyType key) const { return _inputMap.at(key)->_inputData.ButtonDown(); };
    bool ButtonBeingPressed(KeyType key) const { return _inputMap.at(key)->_inputData.ButtonBeingPressed(); };

    std::shared_ptr<KeyEvent> AddEvent(KeyType key, ButtonTypeInputEvent::State state, std::function<void()> eve)
    {
        auto eventRef = GetEvent(key)->AddEvent(state, eve);
        return std::make_shared<KeyEvent>(eventRef, key, state);
    }
    void RemoveEvent(const std::shared_ptr<KeyEvent> eventRef)
    {
        GetEvent(eventRef->_key)->RemoveEvent(eventRef->_state, eventRef->_event);
    }

    //押されたキーを検出する
    KeyType GetInputedType() const;
    //押されたキーのAPI上のキー番号を取得する
    int GetInputedCode() const;
    //API上のキー番号からキーを取得する
    int GetCodeOfType(KeyType type) const;

    ButtonInputData* GetButtonInputData(KeyType key) { return _inputMap.at(key); };

private:

    KeyInput();
    ~KeyInput();

    void RegistRecords();
    void Update();
    void Clear();

    ButtonTypeInput *GetKey(KeyType key) { return &_inputMap.at(key)->_inputData; }
    ButtonTypeInputEvent *GetEvent(KeyType key) { return &_inputMap.at(key)->_inputEvents; }

    class KeyInputData : public ButtonInputData
    {
    public:
        KeyInputData(KeyType type, int value)
            : ButtonInputData(value)
            , _type(type)
        {
        }

        //ライブラリで用意したキー入力識別の列挙型
        KeyType _type;
    };

    void AddRecord(KeyType type, int value);
    std::unordered_map<KeyType, KeyInputData *> _inputMap;
    std::vector<KeyInputData *> _usingInputs;
};

#define KEYBOARD KeyInput::GetInstance()

#endif /* KeyInput_h */
