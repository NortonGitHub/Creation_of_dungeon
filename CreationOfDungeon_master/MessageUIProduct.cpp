#include "MessageUIProduct.h"
#include "DxLib.h"


MessageUIProduct::MessageUIProduct(UIContent ui_contents)
{
    ui = ui_contents;
}


MessageUIProduct::~MessageUIProduct()
{
}

void MessageUIProduct::Update()
{

}

void MessageUIProduct::Draw()
{

    DrawGraph(ui.GetPosX(), ui.GetPosY(), ui.GetGraph().GetGraph(), TRUE);
    DrawString(ui.GetPosX(), ui.GetPosY(), ui.GetStr().c_str(), GetColor(255, 255, 255));

}
