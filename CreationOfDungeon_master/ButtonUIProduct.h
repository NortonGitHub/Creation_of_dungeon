#pragma once
#include "UIProduct.h"

class ButtonUIProduct :
    public UIProduct
{
public:
    ButtonUIProduct(UIContent ui_contents);
    ~ButtonUIProduct();


    std::string Update();
    void Draw();

    void MoveSceneFunction(std::string button_name);
    void QuitFunction();

private:
    bool is_click;

    UIContent ui;

    int test_handle;
};