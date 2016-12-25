#pragma once
#include "UIFactory.h"
class MessageUIFactory :
    public UIFactory
{
public:
    UIProduct* CreateInstance(UIContent ui_contents);

    MessageUIFactory();
    ~MessageUIFactory();

};

