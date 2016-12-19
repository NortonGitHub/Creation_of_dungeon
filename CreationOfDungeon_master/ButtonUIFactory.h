#pragma once
#include "UIFactory.h"
class ButtonUIFactory :
    public UIFactory
{
public:
    UIProduct* CreateInstance();
    
    ButtonUIFactory();
    ~ButtonUIFactory();

};

