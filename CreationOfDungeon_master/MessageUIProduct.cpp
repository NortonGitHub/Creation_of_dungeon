#include "MessageUIProduct.h"
#include "DxLib.h"


MessageUIProduct::MessageUIProduct()
{

}


MessageUIProduct::~MessageUIProduct()
{
}

void MessageUIProduct::Update(UIContent ui)
{

}

void MessageUIProduct::Draw(UIContent ui)
{

    DrawGraph(ui.GetPosX(), ui.GetPosY(), ui.GetGraph().GetGraph(), TRUE);
    DrawString(ui.GetPosX(), ui.GetPosY(), ui.GetStr().c_str(), GetColor(255, 255, 255));

}
