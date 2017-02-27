#pragma once
#include "UIProduct.h"
class GraphUIProduct :
    public UIProduct
{
public:
    GraphUIProduct(UIContent ui_contents);
    ~GraphUIProduct();

    std::string Update();
    void Draw();

    std::string GetUIName() const { return ui.GetDataName(); }

private:
    bool is_click;

    UIContent ui;
};

