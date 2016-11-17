#pragma once
#include <string>
#include "UIProduct.h"
class UIFactory
{
public:
    UIFactory();
    ~UIFactory();

    UIProduct* GetInstance();

private:
    virtual UIProduct* CreateInstance() = 0;

protected:
    UIFactory(std::string file_name);
};

