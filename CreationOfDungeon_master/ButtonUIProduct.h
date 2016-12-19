#pragma once
#include "UIProduct.h"
class ButtonUIProduct :
    public UIProduct
{
public:
    ButtonUIProduct();
    ~ButtonUIProduct();


    void Update(UIContent ui);
    void Draw(UIContent ui);
};

