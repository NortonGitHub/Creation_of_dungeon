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
    ui.Draw();

    auto uiPosition = ui.GetPosition();
    DrawString(static_cast<int>(uiPosition._x),
        static_cast<int>(uiPosition._y),
        ui.GetStr().c_str(),
        GetColor(255, 255, 255));
}
