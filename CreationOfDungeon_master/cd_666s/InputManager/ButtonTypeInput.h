#pragma once

class ButtonTypeInput
{
public:
    ButtonTypeInput();
    ~ButtonTypeInput();
    
    //前フレームで押されず、現フレームで押されているか
    bool ButtonDown() const { return (_isPressing && !_beforeFramePressed); };
    //前フレームで押され、現フレームで離されたか
    bool ButtonUp() const { return (!_isPressing && _beforeFramePressed); };
    //現フレームで押されているか
    bool ButtonBeingPressed() const { return _isPressing; };
    
    //現フレームで押され続けて何フレーム目か
    int GetInputingFrame() const { return _inputingFrame; }
    
    //入力状態を確認
    void UpdateState(bool state);
    
private:
    
    //ボタンが押され続けてるフレーム数
    int _inputingFrame;
    //現フレームで押されているか
    bool _isPressing;
    //前フレームで押されていたか
    bool _beforeFramePressed;
};

