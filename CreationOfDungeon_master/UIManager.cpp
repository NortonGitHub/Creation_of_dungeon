#include "UIManager.h"
#include "UIFactory.h"
#include "CSVDataLoader.h"

#include "MessageUIFactory.h"
#include "ButtonUIFactory.h"
#include "GraphUIFactory.h"

#include <string>

UIManager::UIManager() {
}


UIManager::UIManager(std::string scene_name)
{
    /***Sample Code***
    UIFactory* a = new MessageUIFactory();

    UIProduct* p = a->GetInstance();

    p->Update();    //このクラスのUpdate()内で呼び出し
    ****Sample Code***/

    using_UI.reserve(5);
    ui_products.reserve(5);
    factory.reserve(4);

    factory["message"] = new MessageUIFactory();
    factory["select"] = new ButtonUIFactory();
    factory["graph"] = new GraphUIFactory();


    Init(scene_name);
}

UIManager::~UIManager()
{
}

void UIManager::Init(std::string scene_name) {

    CSVDataLoader::LoadUICSV(using_UI, scene_name);

    for (auto ui : using_UI) {
        std::string data_name = ui.GetDataName();
        

        //もしfactory配列のキーにdata_nameと同名のそれがあればui_productsにインスタンスを追加する
        if (factory.find(data_name) != factory.end()) {

            auto temp = factory[data_name]->GetInstance();
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
    }
}

void UIManager::Update() {
    auto ui = using_UI;
    for (auto pro : ui_products) {
        if (pro != nullptr) {
            pro->Update(ui);
        }
    }

    //using_UI = ui;
    std::copy(ui.begin(),ui.end(),std::back_inserter(using_UI));

#if 0
    for (auto ui : using_UI) {
        
    }
#endif
}

void UIManager::Draw()
{
    auto ui = using_UI;
    for (auto pro : ui_products) {
        if (pro != nullptr) {
            pro->Draw(ui);
        }
    }
}
