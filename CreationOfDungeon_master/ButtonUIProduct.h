#pragma once
#include "UIProduct.h"
class ButtonUIProduct :
    public UIProduct
{
public:
    ButtonUIProduct(UIContent ui_contents);
    ~ButtonUIProduct();


    void Update();
    void Draw();

    void A() {};

private:
    bool is_click;

    UIContent ui;
};

