#include "EditMap.h"
#include "FunctionTransScene.h"
#include "PanelBase.h"

#include "PanelAffectObjects.h"
#include "PanelDisplayer.h"
#include "PanelSceneTransition.h"
#include "PanelSettingObject.h"


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

    std::string _ui_name;

    std::function<PanelBase()> a = [&] {
        return PanelBase();
    };

    a();

    std::function<PanelBase()> as[4] = {
       [&] {
            return PanelAffectObjects();
       },
       [&] {
           return PanelSettingObject();
       },
       [&] {
           return PanelSceneTransition();
       },
       [&] {
           return PanelDisplayer();
       }
    };

    std::multimap<std::string, PanelBase> paneltypes;

    paneltypes.emplace("CHANGE_LIST", as[0]);
    paneltypes.emplace("SELECT_OBJ", as[1]);
    paneltypes.emplace("MOVE", as[2]);
    paneltypes.emplace("SHOW", as[3]);

    std::vector<PanelBase> ps;  //test

    for (auto p : ps) {
        /*PanelBase以下のクラスに、カーソルとパネルが重なっているかを確かめるための関数を用意する*/
        if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) {
            paneltypes.find("");
        }
    }
    /*以上では目的は達せられない*/

    PanelBase ukemi;

    std::function<PanelBase()> test2 = [&]{

    };


    for (auto p : ps) {
        if(0){
            test2;
        }
    }

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
