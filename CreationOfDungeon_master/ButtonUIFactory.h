#pragma once
#include "UIFactory.h"
class ButtonUIFactory :
    public UIFactory
{
public:
    UIProduct* CreateInstance(UIContent ui_contents);
    
    ButtonUIFactory();
    ~ButtonUIFactory();

};

