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
    ui.Draw();

    auto uiPosition = ui.GetPosition();
    DrawString(static_cast<int>(uiPosition._x),
        static_cast<int>(uiPosition._y),
        ui.GetStr().c_str(),
        GetColor(255, 255, 255));

}

