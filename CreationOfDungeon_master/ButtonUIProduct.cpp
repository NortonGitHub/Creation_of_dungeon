#include "ButtonUIProduct.h"
#include "DxLib.h"
#include "MouseManager.h"

ButtonUIProduct::ButtonUIProduct(UIContent ui_contents)
{
    is_click = false;

    ui = ui_contents;
    ui.SetFunction(GetUI(ui.GetDataName()));
}


ButtonUIProduct::~ButtonUIProduct()
{
}

void ButtonUIProduct::Update()
{
    if (MouseManager::IsClicked("left", is_click)) {
        ui.GetFunction();
    }
}

void ButtonUIProduct::Draw()
{
    ui.GetGraph().Draw();
}