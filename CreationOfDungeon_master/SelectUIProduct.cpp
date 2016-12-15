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
    ui.Draw();

    auto uiPosition = ui.GetPosition();
    DrawString(static_cast<int>(uiPosition._x),
        static_cast<int>(uiPosition._y),
        ui.GetStr().c_str(),
        GetColor(255, 255, 255));
}