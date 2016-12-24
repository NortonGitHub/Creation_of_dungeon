#include "GraphUIProduct.h"



GraphUIProduct::GraphUIProduct(UIContent ui_contents)
{
    ui = ui_contents;
}


GraphUIProduct::~GraphUIProduct()
{
}

std::string GraphUIProduct::Update()
{
    return "";
}

void GraphUIProduct::Draw()
{
    ui.Draw();
}
