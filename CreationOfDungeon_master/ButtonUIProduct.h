#pragma once
#include "UIProduct.h"
#include "SceneBase.h"
class ButtonUIProduct :
    public UIProduct
{
public:
    ButtonUIProduct(UIContent ui_contents);
    ~ButtonUIProduct();


    void Update();
    void Draw();

    SceneBase* MoveSceneFunction();
    void QuitFunction();

private:
    bool is_click;

    UIContent ui;

    int test_handle;


};

