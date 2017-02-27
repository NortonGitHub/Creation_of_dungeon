#pragma once
#include "UIProduct.h"
class MessageUIProduct :
    public UIProduct
{
public:
    MessageUIProduct(UIContent ui_contents);
    ~MessageUIProduct();

    std::string Update();
    void Draw();

    std::string GetUIName() const { return ui.GetDataName(); };

private:
    bool is_click;

    UIContent ui;
};

