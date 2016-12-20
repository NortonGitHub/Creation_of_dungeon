#pragma once
#include <string>
#include "UIProduct.h"
class UIFactory
{
public:
    UIFactory();
    ~UIFactory();

    UIProduct* GetInstance(UIContent ui_contents);

private:
    virtual UIProduct* CreateInstance(UIContent ui_contents) = 0;

protected:
    UIFactory(std::string file_name);
};

