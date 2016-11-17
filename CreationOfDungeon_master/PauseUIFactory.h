#pragma once
#include "UIFactory.h"
class PauseUIFactory :
    public UIFactory
{
public:
    UIProduct* CreateInstance();

    PauseUIFactory();
    ~PauseUIFactory();

};

