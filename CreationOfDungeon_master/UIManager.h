#pragma once
#include <vector>
#include <unordered_map>
#include <iterator>
#include "UIContent.h"
#include "UIProduct.h"

#include "MouseContent.h"

class UIManager
{
public:
    UIManager();
    UIManager(std::string scene_name);
    ~UIManager();

    void Update(std::vector<std::string> &_functions, std::string &_obj_name);
    void Draw();

    void Init(std::string scene_name);

    std::string GetFunctionEffect();

private:
    std::vector<UIContent> using_UI;
    std::vector<UIProduct*> ui_products;
    //    std::unordered_map<std::string, UIFactory*> factory;

    std::function<void()> SetUIFunction(std::string func_name);

    Graph test;
    int test2;
};

