#include "InputManager.h"

InputManager::InputManager()
{
}


void InputManager::Update()
{
    KEYBOARD->Update();
    MOUSE->Update();
}


void InputManager::Clear()
{
    KEYBOARD->Clear();
    MOUSE->Clear();
    CUSTOM_INPUT->Clear();
}