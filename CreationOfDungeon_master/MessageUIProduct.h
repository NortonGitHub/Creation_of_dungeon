#pragma once
#include "UIProduct.h"
class MessageUIProduct :
    public UIProduct
{
public:
    MessageUIProduct();
    ~MessageUIProduct();

    void Update(UIContent ui);
    void Draw(UIContent ui);
};

