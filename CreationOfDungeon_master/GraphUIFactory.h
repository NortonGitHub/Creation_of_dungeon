#pragma once
#include "UIFactory.h"
class GraphUIFactory :
    public UIFactory
{
public:
    GraphUIFactory();
    ~GraphUIFactory();

    UIProduct* CreateInstance(UIContent ui_contents);
};

