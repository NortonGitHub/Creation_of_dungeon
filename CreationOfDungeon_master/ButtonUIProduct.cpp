#include "ButtonUIProduct.h"
#include "DxLib.h"


ButtonUIProduct::ButtonUIProduct()
{
}


ButtonUIProduct::~ButtonUIProduct()
{
}

void ButtonUIProduct::Update(UIContent ui)
{
}

void ButtonUIProduct::Draw(UIContent ui)
{

    DrawGraph(ui.GetPosX(), ui.GetPosY(), ui.GetGraph().GetGraph(), TRUE);
    DrawString(ui.GetPosX(), ui.GetPosY(), ui.GetStr().c_str(), GetColor(255, 255, 255));
}