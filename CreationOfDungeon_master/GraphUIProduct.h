#pragma once
#include "UIProduct.h"
class GraphUIProduct :
    public UIProduct
{
public:
    GraphUIProduct();
    ~GraphUIProduct();

    void Update(UIContent ui);
    void Draw(UIContent ui);
};

