#include "PauseUIProduct.h"
#include "DxLib.h"


PauseUIProduct::PauseUIProduct()
{
}


PauseUIProduct::~PauseUIProduct()
{
}

void PauseUIProduct::Update(UIContent ui)
{
}

void PauseUIProduct::Draw(UIContent ui)
{
    DrawGraph(ui.GetPosX(), ui.GetPosY(), ui.GetGraph().GetGraph(), TRUE);
    DrawString(ui.GetPosX(), ui.GetPosY(), ui.GetStr().c_str(), GetColor(255, 255, 255));
}

