#pragma once
#include "UIContent.h"
class UIProduct
{
public:
    UIProduct();
    ~UIProduct();

    void Update(std::vector<UIContent>& using_UI);
    virtual void Update(UIContent ui) = 0;
    void Draw(std::vector<UIContent>& using_UI);
    virtual void Draw(UIContent ui) = 0;

};

