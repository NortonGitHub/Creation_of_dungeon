#include "MiniSelectUIProduct.h"
#include "DxLib.h"


MiniSelectUIProduct::MiniSelectUIProduct()
{
}


MiniSelectUIProduct::~MiniSelectUIProduct()
{
}

void MiniSelectUIProduct::Update(UIContent ui)
{
}

void MiniSelectUIProduct::Draw(UIContent ui)
{
    DrawGraph(ui.GetPosX(), ui.GetPosY(), ui.GetGraph().GetGraph(), TRUE);
    DrawString(ui.GetPosX(), ui.GetPosY(), ui.GetStr().c_str(), GetColor(255, 255, 255));
}
