#pragma once
#include "ControllerBase.h"


class KeyManager :
    public ControllerBase
{
public:
    KeyManager(const KeyManager&) = delete;
    
    static KeyManager& GetInstance() {
        static KeyManager k;
        return k;
    }
    
private:
    KeyManager() = default;
    ~KeyManager() = default;

    int GetMousePush();
};

