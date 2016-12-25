#include "MessageUIProduct.h"
#include "DxLib.h"


MessageUIProduct::MessageUIProduct(UIContent ui_contents)
{
    ui = ui_contents;
}


MessageUIProduct::~MessageUIProduct()
{
}

std::string MessageUIProduct::Update()
{
    return "";
}

void MessageUIProduct::Draw()
{
    ui.Draw();
}
