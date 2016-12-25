#pragma once
#include <unordered_map>
#include "../Utility/Singleton.h"
#include "ButtonTypeInput.h"
#include "ButtonTypeInputEvent.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "CustomInput.h"

class InputManager : public Singleton<InputManager>
{
    friend class Singleton<InputManager>;
    
public:
        
    void Clear();
    void Update();

private:
    
    InputManager();
    ~InputManager(){};
};

#define INPUT_MGR InputManager::GetInstance()