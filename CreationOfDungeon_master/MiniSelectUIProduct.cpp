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
    ui.Draw();

    auto uiPosition = ui.GetPosition();
    DrawString(static_cast<int>(uiPosition._x), 
        static_cast<int>(uiPosition._y), 
        ui.GetStr().c_str(), 
        GetColor(255, 255, 255));
}
