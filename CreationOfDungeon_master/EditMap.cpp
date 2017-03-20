#include "EditMap.h"
#include "FunctionTransScene.h"
#include "PanelBase.h"

#include "PanelAffectObjects.h"
#include "PanelDisplayer.h"
#include "PanelSceneTransition.h"
#include "PanelSettingObject.h"


#include <typeinfo>


EditMap::EditMap(std::string _stage_num)
    : stage_num(_stage_num)
{
    _functions.reserve(20);
    class_name = "editmap";
    Init();
}


EditMap::~EditMap()
{
    _functions.clear();
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

#if 0
    /*試しコード*/
    /*NOTE*/
    /*
        PanelBaseには、そのパネルの名前、座標、変数が格納されている
        変数は子クラスごとに異なるので注意
    */
    std::vector<PanelBase> panels; //試験コード用

    /*
        別のオブジェクトへのアクセスが必要になった際に
        対象となるオブジェクトを格納する
        配列 ならびに 簡易関数
    */
    /*multimap キー:カテゴリ名, 値:対象のクラス型オブジェクト*/
    std::multimap<std::string, PanelBase> _targets;
    auto SetClassType = [&](std::string _category) {
        _targets.clear();
        for (auto ps : panels) {
            if (ps.GetCategoryName() == _category) {
                _targets.emplace(_category, ps);
            }
        }
    };
    /*↑の処理
    無意味じゃない？
     -> 大本の配列panelsの中の、型がクラスPanelSettingObject
     の要素のPanelContentを書き換えるのだから、
     ただ消すだけでいい
    */

    for (auto p : panels) {
        //
        bool isClicked = p.IsClicked();

        //何かのオブジェクトがクリック
        //そのオブジェクトの種類(クラス)によって
        //処理内容が変化する。
        //また、別のサブクラスのオブジェクトに
        //干渉する


        //オブジェクトがクリックされたら
        if (isClicked) {
            auto str = std::string(typeid(p).name());

            if (str.find("AffectObjects") != std::string::npos) {
#if 0
                std::map<std::string, PanelBase> panel_temps;//消すかも
                std::string _category = p.GetCategoryName();

                for (auto sp : panels) {
                    std::string str_s = sp.GetCategoryName();
                    if (str_s.find(_category) == std::string::npos) {
                        panel_temps.insert(_category, sp);
                    }
                }
#endif
                SetClassType(p.GetCategoryName());

                for (auto _obj : _targets) {

                    p.SetObject(_obj.second);
                }
            }

            p.Update();
        }
    }



#endif

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

    _dungeon->Update();

    return this;
}

void EditMap::Draw()
{
    _dungeon->Draw();
}

void EditMap::Init()
{
    _dungeon = std::make_shared<MakeDungeon>(stage_num);
    _dungeon->Init();
}
