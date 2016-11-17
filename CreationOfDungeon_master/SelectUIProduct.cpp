#include "SelectUIProduct.h"
#include "DxLib.h"


SelectUIProduct::SelectUIProduct()
{
}


SelectUIProduct::~SelectUIProduct()
{
}

void SelectUIProduct::Update(UIContent ui)
{
}

void SelectUIProduct::Draw(UIContent ui)
{

    DrawGraph(ui.GetPosX(), ui.GetPosY(), ui.GetGraph().GetGraph(), TRUE);
    DrawString(ui.GetPosX(), ui.GetPosY(), ui.GetStr().c_str(), GetColor(255, 255, 255));
}