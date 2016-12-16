#pragma once
#include <vector>
#include <unordered_map>
#include <iterator>
#include "UIFactory.h"
#include "UIContent.h"

class UIManager
{
public:
    UIManager();
    UIManager(std::string scene_name);
    ~UIManager();

    void Update();
    void Draw();

    void Init(std::string scene_name);

private:
    std::vector<UIContent> using_UI;
    std::vector<UIProduct*> ui_products;
    std::unordered_map<std::string, UIFactory*> factory;

};

