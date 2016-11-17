#pragma once
#include "UIFactory.h"
class MessageUIFactory :
    public UIFactory
{
public:
    UIProduct* CreateInstance();

    MessageUIFactory();
    ~MessageUIFactory();

};

