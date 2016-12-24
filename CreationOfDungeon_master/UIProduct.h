#pragma once
#include "UIContent.h"

class UIProduct
{
public:
    UIProduct();
    ~UIProduct();

//    void Update(std::vector<UIContent>& using_UI);
    virtual std::string Update() = 0;
//    void Draw(std::vector<UIContent>& using_UI);
    virtual void Draw() = 0;
    
protected:
    std::function<void()> GetUI(std::string data_name);
};

