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

    //NOTE:
    //各個別UIに種類別の情報を格納し、
    //またほかのUIからの戻り値や情報の変化によってその値を返したり変更したりする
    //仕組みを考案する必要がある

    std::string _ui_name;

#if 1
    /*NOTE*/
    /*
        PanelBaseには、そのパネルの名前、座標、変数が格納されている
        変数は子クラスごとに異なるので注意
    */
    std::vector<PanelBase> panels; //試験コード用

    for(auto p : panels){
        //
        bool isClicked = p.IsClicked();

        if(isClicked){
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
