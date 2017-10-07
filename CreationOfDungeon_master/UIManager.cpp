#include "UIManager.h"
#include "CSVDataLoader.h"

/*
#include "MessageUIFactory.h"
#include "ButtonUIFactory.h"
#include "GraphUIFactory.h"
*/

#include "MessageUIProduct.h"
#include "ButtonUIProduct.h"
#include "GraphUIProduct.h"

#include "MouseManager.h"

#include <string>

#include "DxLib.h"

#include<iostream>
#include<fstream>

UIManager::UIManager() {
}


UIManager::UIManager(std::string scene_name) : test("resource/test_666/omote.png")
{
    /***Sample Code***
    UIFactory* a = new MessageUIFactory();

    UIProduct* p = a->GetInstance();

    p->Update();    //このクラスのUpdate()内で呼び出し
    ****Sample Code***/

    using_UI.reserve(5);
    ui_products.reserve(5);
    //    factory.reserve(4);

    /*    factory["message"] = new MessageUIFactory();
        factory["button"] = new ButtonUIFactory();
        factory["graph"] = new GraphUIFactory();*/

    test.SetPosition(Vector2D(128, 0));

    test2 = LoadGraph("resource/test_666/omote.png");

    Init(scene_name);
}

UIManager::~UIManager()
{
    using_UI.shrink_to_fit();
    ui_products.shrink_to_fit();
    //    factory.clear();
}

void UIManager::Init(std::string scene_name) {

    CSVDataLoader::LoadUICSV(using_UI, scene_name);

    auto a = using_UI.begin();

    for (std::vector<UIContent>::iterator ui = using_UI.begin(); ui != using_UI.end(); ui++) {

        //ui->SetFunction(SetUIFunction(ui->GetDataName()));

        std::string type_name = ui->GetTypeName();

        if (type_name.find("message") != std::string::npos) {
            ui_products.push_back(new MessageUIProduct(*ui));
        }
        else if (type_name.find("button") != std::string::npos) {
            ui_products.push_back(new ButtonUIProduct(*ui));
        }
        else if (type_name.find("graph") != std::string::npos) {
            ui_products.push_back(new GraphUIProduct(*ui));
        }

#if 0
        //もしfactory配列のキーにdata_nameと同名のそれがあればui_productsにインスタンスを追加する
        if (factory.find(type_name) != factory.end()) {

            auto temp = factory[type_name]->GetInstance(*ui);
            ui_products.push_back(temp);

#if 0
            auto itr = std::find(ui_products.begin(), ui_products.end(), temp);

            if (itr == ui_products.end()) {
                ui_products.push_back(temp);
            }
#endif

        }
        else {
            ui_products.push_back(nullptr);
        }
#endif
    }
}

std::string UIManager::GetFunctionEffect()
{



    return "";
}

std::function<void()> UIManager::SetUIFunction(std::string func_name)
{
    return std::function<void()>();
}

void UIManager::Update(std::vector<std::string> &_functions, std::string &_obj_name) {

    std::string func_name = "";

    for (auto pro : ui_products) {
        if (pro != nullptr) {
            func_name = pro->Update();
            if (func_name != "") {
                _functions.push_back(func_name);
                _obj_name = pro->GetUIName();
            }
        }
    }
#if 0
    for (auto ui : using_UI) {

    }
#endif
}

void UIManager::Draw()
{
    for (auto pro : ui_products) {
        if (pro != nullptr) {
            pro->Draw();
        }
    }
    int a = ui_products.size();
    //表示可能
    //DrawGraph(300, 100, test2, FALSE);
}
