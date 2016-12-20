#pragma once
#include "UIProduct.h"
class GraphUIProduct :
    public UIProduct
{
public:
    GraphUIProduct(UIContent ui_contents);
    ~GraphUIProduct();

    void Update();
    void Draw();

private:
    bool is_click;

    UIContent ui;
};

