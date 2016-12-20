#pragma once
#include "UIProduct.h"
class MessageUIProduct :
    public UIProduct
{
public:
    MessageUIProduct(UIContent ui_contents);
    ~MessageUIProduct();

    void Update();
    void Draw();

private:
    bool is_click;

    UIContent ui;
};

