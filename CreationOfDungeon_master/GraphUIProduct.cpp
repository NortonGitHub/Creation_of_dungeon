#include "GraphUIProduct.h"



GraphUIProduct::GraphUIProduct(UIContent ui_contents) : ui(ui_contents)
{
    is_click = false;
}


GraphUIProduct::~GraphUIProduct()
{
}

std::string GraphUIProduct::Update()
{
    return "NONE";
}

void GraphUIProduct::Draw()
{
    ui.Draw();
}
