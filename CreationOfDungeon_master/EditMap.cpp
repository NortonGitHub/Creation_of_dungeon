#include "EditMap.h"
#include "FunctionTransScene.h"
#include "PanelBase.h"

#include "PanelAffectObjects.h"
#include "PanelDisplayer.h"
#include "PanelSceneTransition.h"
#include "PanelSettingObject.h"

#include "cd_666s/Utility/CSVReader.h"
#include "cd_666s/Resources/AllResourceManager.h"

#include "PanelObjectManager.h"

#include <typeinfo>
#include <sstream>

#include <assert.h>

EditMap::EditMap(std::string _stage_num)
    : stage_num(_stage_num), NPOS(std::string::npos)
{
    _functions.reserve(20);
    //panels.reserve(30);
    class_name = "editmap";

    Init();
}


EditMap::~EditMap()
{
    _functions.clear();

    PANEL_MGR->Clear();

    PANEL_MGR->Refresh();

#if 1
    std::string pass = RESOURCE_TABLE->GetFolderPath();
    std::string str = "csv/Stagedata/template.csv";
    pass += str;
    std::remove(pass.c_str());
#endif
}

SceneBase * EditMap::Update(UIManager _ui)
{
    //std function に変更する？
    _functions.resize(0);

    //NOTE:
    //各個別UIに種類別の情報を格納し、
    //またほかのUIからの戻り値や情報の変化によってその値を返したり変更したりする
    //仕組みを考案する必要がある

    std::string _ui_name;

#if 1
    /*試しコード*/
    /*NOTE*/
    /*
        PanelBaseには、そのパネルの名前、座標、変数が格納されている
        変数は子クラスごとに異なるので注意
    */
    //std::vector<PanelBase> panels; //試験コード用

    /*
        別のオブジェクトへのアクセスが必要になった際に
        対象となるオブジェクトを格納する
        配列 ならびに 簡易関数
    */
    /*multimap キー:カテゴリ名, 値:対象のクラス型オブジェクト*/
    std::multimap<std::string, PanelBase> _targets;
    auto SetClassType = [&] {
        _targets.clear();
    };

    auto scene = PanelFunction();



#endif

#if 0
    _ui.Update(_functions, _ui_name);

    for (auto f : _functions) {
        if (f.find("CHANGE_LIST") != std::string::npos) {

            //_se.Play();
        }
        else if (f.find("SHOW") != std::string::npos) {
            //_se.Play();
        }
        else if (f.find("MOVE") != std::string::npos) {
            //_se.Play();
        }
        else if (f.find("SELECT_OBJECT") != std::string::npos) {
            _dungeon->PickupObject();
            //_se.Play();
        }

    }
#endif

    for (auto p : PANEL_MGR->_objects) {
        if (p != nullptr)
            p->Update();
    }

    //_dungeon->Update();

    return scene;
}

void EditMap::Draw()
{
    //_dungeon->Draw();

    for (auto p : PANEL_MGR->_objects) {
        if (p != nullptr)
            p->Draw();
    }

    PANEL_MGR->Refresh();

}

void EditMap::Init()
{
    //パネルの読み込み
    CSVReader reader;
    std::vector<std::string> panels_str;
    std::string filename = "csv/Panel/";
    filename += class_name + ".csv";
    reader.Read(RESOURCE_TABLE->GetFolderPath() + filename, panels_str, 1);

    /*stringを各要素ごとに代入*/
    /*
    std::map<std::string, std::shared_ptr<PanelBase>> panelTypes;
    panelTypes.insert(std::make_pair("CHANGE_LIST",new PanelAffectObjects()));
    panelTypes.insert(std::make_pair("MOVE", new PanelSceneTransition()));
    panelTypes.insert(std::make_pair("SELECT_OBJ", new PanelSettingObject()));
    panelTypes.insert(std::make_pair("SHOW", new PanelDisplayer()));
    auto b = panelTypes.begin();
    */

    DebugOutputFile();

    //ここにPANEL_MGR追加処理を
    int elem_count = 0;
    std::vector<std::string> panel_temp;
    std::vector<PanelContent> panel_cont_temp;
    panel_cont_temp.reserve(30);

    /******オブジェクト設置パネル ファイル読み込み　開始*******/
    const std::string panel_category[3] = { "BLOCK","MONSTER","TRAP" };

    for (auto panel_c : panel_category) {
        std::string fileName = "csv/Edit/";
        fileName += panel_c + ".csv";
        std::vector<std::string> _array;

        reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, _array, 1);

        for (auto f : _array) {
            std::string filename = panel_c + "/" + f;

            //選択用のパネルの情報を初期化代入
            auto panelTemp = std::make_shared<PanelSettingObject>(PanelContent(filename));

            //オブジェクト設置パネルのすべてのカテゴリ分をmap配列に挿入
            //_allSettingPanel.insert(std::make_pair(panel_c, std::make_shared<PanelSettingObject>(panelTemp)));
            _allSettingPanel.insert(std::make_pair(panel_c, panelTemp));
        }
    }
    /******オブジェクト設置パネル ファイル読み込み　終了*******/


#if 1
    auto& panel_obj = PANEL_MGR->_objects;

    for (std::string p : panels_str) {
        if (p != "") {
            panel_temp.push_back(p);
            if (elem_count >= 4) {

                try {
                    std::shared_ptr<PanelBase> temp;

                    auto temp2 = std::make_shared<PanelContent>(Vector2D(std::stoi(panel_temp[0]), std::stoi(panel_temp[1])), panel_temp[2], panel_temp[4]);

                    SetPanelInstance(panel_temp[3], temp, *temp2);

                    panel_obj.push_back(temp);

                    panel_obj.back()->Init(PanelContent(Vector2D(std::stoi(panel_temp[0]),
                        std::stoi(panel_temp[1])), panel_temp[2], panel_temp[4]));


                    panel_obj.back()->DrawDebugPrint();

                    //panel_cont_temp.push_back(PanelContent(
                    //    Vector2D(std::stoi(panel_temp[0]), std::stoi(panel_temp[1])), panel_temp[2], panel_temp[4]));
                }
                catch (std::out_of_range&) {
                    assert("Cannot push_back panel elem");
                }
                panel_temp.clear();
                elem_count = 0;
            }
            else {
                elem_count++;
            }
        }
    }

    std::string file_name = (IsFirstWave() ? "template" : "map" + stage_num);

    PANEL_MGR->Refresh();

    /*
    auto _s = panel_cont_temp.size();
    int elem = 0;
    for (auto& obj : panel_obj) {
        if (obj.get() != nullptr) {
            obj->Init(panel_cont_temp[elem]);
            obj->DrawDebugPrint();
        }
        elem++;
    }
    */

    /*
    _dungeon = std::make_shared<MakeDungeon>(stage_num);
    _dungeon->Init(file_name);
    */

    panel_cont_temp.clear();
#endif
}

bool EditMap::IsFirstWave()
{
    CSVReader reader;

    std::string filePass = "csv/StageData/";
    std::string fileName = filePass + "template.csv";
    std::vector<std::string> stage_data;

    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, stage_data, 0);
    auto b = stage_data.size();
    //ステージデータが無い(=第1ウェーブ)の場合
    if (stage_data.empty()) {
        //templateファイルの生成
        //std::ofstream(RESOURCE_TABLE->GetFolderPath() + fileName);
        return false;
    }
    return true;
}

SceneBase * EditMap::PanelFunction()
{

    for (auto p : PANEL_MGR->_objects) {

        if (p == nullptr)
            continue;

        //
        bool isClicked = p->IsClicked();

        //何かのパネルがクリックされる。
        //そのパネルの種類(クラス)によって
        //処理内容が変化する。
        //また、別のサブクラスのパネルの変数に
        //干渉する

        //パネルがクリックされたら
        if (isClicked) {
            //問題点 どうあがいてもPanelBaseが返される
            //auto str = std::string(typeid(p).name());
            auto str = p->GetTypeName();

            //クリックされたパネルの名前が"AffectObjects"だった場合
            if (str.find("AffectObject") != NPOS) {
                PanelAffectObjectsFunction(*p);
            }
            else if (str.find("Displayer") != NPOS) {
                PanelDisplayerFunction(*p);
            }
            else if (str.find("SceneTrans") != NPOS) {
                PanelSceneTransFunction(*p);
            }
            else if (str.find("SettingObject") != NPOS) {
                PanelSettingObjectFunction(*p);
            }

            p->Update();
        }
    }

    return this;
}

void EditMap::PanelAffectObjectsFunction(PanelBase& panel)
{
    //std::vector<std::shared_ptr<PanelBase>> temp_p;
    std::vector<PanelBase> temp_p;

    /*値を変化させる他パネルを検索する*/
    auto& ps = PANEL_MGR->_objects;
    for (auto& p : ps) {
        if (p == nullptr)
            continue;

        auto aff_str = p->GetTypeName();

        //カテゴリー名が一致したものをpに上書きする
        if (aff_str.find("SettingObject") != NPOS) {
            //temp_p.push_back(*ps);
            //auto b = temp_p.back(); //テスト用

            auto obj = _allSettingPanel.find(p->GetCategoryName());

            if (obj != _allSettingPanel.end()) {
                p = std::move(obj->second);
            }
        }
    }



    /***一時的にコメントアウト中***/
    //panel.SetSettingObject(temp_p);
    int j = 0;
    /*
    auto& obj = PANEL_MGR->_objects;

    for (int i = 0; i < obj.size(); i++) {
        if (obj[i] == nullptr)
            continue;

        auto aff_str = obj[i]->GetTypeName(); //std::string(typeid(obj).name());
        if (aff_str.find("SettingObject") != NPOS) {
            *obj[i] = temp_p[j];
            auto o = obj[i];
            auto t = temp_p[j];
            j++;
        }
    }
    */
}

void EditMap::PanelDisplayerFunction(PanelBase& panel)
{
}

void EditMap::PanelSceneTransFunction(PanelBase& panel)
{
}

void EditMap::PanelSettingObjectFunction(PanelBase& panel)
{
}

void EditMap::SetPanelInstance(std::string key_name, std::shared_ptr<PanelBase>& panel, PanelContent& temp)
{
    if (key_name == "CHANGE_LIST") {
        panel = std::make_shared<PanelAffectObjects>(temp);
    }
    else if (key_name == "MOVE") {
        panel = std::make_shared<PanelSceneTransition>(temp);
    }
    else if (key_name == "SELECT_OBJ") {
        panel = std::make_shared<PanelSettingObject>(temp);
    }
    else if (key_name == "SHOW") {
        panel = std::make_shared<PanelDisplayer>(temp);
    }
}

void EditMap::DebugOutputFile()
{
    std::ofstream writing_file;
    writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::out);
    writing_file.close();
}
