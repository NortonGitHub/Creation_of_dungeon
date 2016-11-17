#pragma once
#include "UIFactory.h"
class MiniSelectUIFactory :
    public UIFactory
{
public:
    UIProduct* CreateInstance();

    MiniSelectUIFactory();
    ~MiniSelectUIFactory();

};

