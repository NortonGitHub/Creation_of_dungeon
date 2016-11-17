#pragma once
#include "UIProduct.h"
class PauseUIProduct :
    public UIProduct
{
public:
    PauseUIProduct();
    ~PauseUIProduct();


    void Update(UIContent ui);
    void Draw(UIContent ui);
};

