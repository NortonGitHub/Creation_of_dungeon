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

#include "cd_666s/TilebaseAI/TileField.h"
#include "cd_666s/TilebaseAI/TiledObjectMnager.h"

#include "cd_666s/DebugDraw.h"

#include "Game.h"

#include "cd_666s\TilebaseAI\Enemy.h"
#include "cd_666s\TilebaseAI\AI\AstarPathFinder.h"

#include <typeinfo>
#include <sstream>

#include <iostream>

#include <assert.h>

#define STR(var) #var


EditMap::EditMap(std::string _stage_num)
    : stage_num(_stage_num), NPOS(std::string::npos)
{
    _functions.reserve(20);
    //panels.reserve(30);
    class_name = "editmap";



    _selectCategoryGr.Load("resource/graph/ui/SelectTypeFrame.png");
    _selectCategoryGr.SetPriority(static_cast<int>(Sprite::Priority::UI) + 1);

    _selectCategoryGr.SetDisplayMode(false);
    
    _selectObjectGr.Load("resource/graph/ui/SelectObjectFrame.png");
    _selectObjectGr.SetPriority(static_cast<int>(Sprite::Priority::UI) + 1);
    
    _selectObjectGr.SetDisplayMode(false);

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

    for(auto p : PANEL_MGR->_objects){
        if (p != nullptr)
            p->Update();
    }

    _dungeon->Update();

    SetObject();

    DeleteAddedObject();

    return scene;
}

void EditMap::Draw()
{
    _dungeon->Draw();

    for (auto& p : PANEL_MGR->_objects) {
        if (p != nullptr)
            p->Draw();
    }

    PANEL_MGR->Refresh();

    std::string debugStr = "設置上限\n";
    debugStr += "モンスター:" + std::to_string(set_count["MONSTER"]) + "/" + std::to_string(LIMIT_MONSTER)+ " ";
    debugStr += "トラップ:" + std::to_string(set_count["TRAP"]) + "/" + std::to_string(LIMIT_TRAP) + "\n";
    debugStr += "ブロック:" + std::to_string(set_count["BLOCK"]) + "/" + std::to_string(LIMIT_BLOCK) + "\n";

    Debug::DrawString(Vector2D(980, 140), debugStr,Color4(0,0,0,0),16);



    std::string pageStr = "";

    if (selectPanelCategory.find("MONSTER") != std::string::npos) {
        pageStr += "1/1";
    }
    else if (selectPanelCategory.find("TRAP") != std::string::npos) {
        pageStr += "1/1";
    }
    else if (selectPanelCategory.find("BLOCK") != std::string::npos) {
        pageStr += "1/1";
    }
    else {
        pageStr += "0/0";
    }

    Debug::DrawString(Vector2D(1055, 270), pageStr, Color4(0, 0, 0, 0), 40);


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
    std::vector<PanelContent> panel_cont_temp(1);
    panel_cont_temp.reserve(30);

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
                    
                    //panel_cont_temp.push_back(PanelContent(
                        //Vector2D(std::stoi(panel_temp[0]), std::stoi(panel_temp[1])), panel_temp[2], panel_temp[4]));
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
    int elem = 0;
    for (auto obj : panel_obj) {
        if (obj.get() != nullptr) {
            obj->Init(panel_cont_temp[elem]);
            obj->DrawDebugPrint();
        }
        elem++;
    }
    */
    
    _dungeon = std::make_shared<MakeDungeon>(stage_num);
    _dungeon->Init(file_name);

    panel_cont_temp.clear();
    
    selectedObject.reset();

    selectPanelCategory = "";

    addTiledObjectList_Trap.clear();
    addTiledObjectList_Block.clear();

    /***各オブジェクト設置数カウンタ初期化***/
    set_count.insert({ "BLOCK", 0 });
    set_count.insert({ "MONSTER", 0 });
    set_count.insert({ "TRAP", 0 });
    //set_count[0] = 0;
    //set_count[1] = 0;
    //set_count[2] = 0;
    /***各オブジェクト設置数カウンタ初期化 ここまで***/

    if (stage_num != "3") {
        LIMIT_TRAP = 3;
        LIMIT_MONSTER = 3;
        LIMIT_BLOCK = 6;
    }
    else {
        LIMIT_TRAP = 4;
        LIMIT_MONSTER = 4;
        LIMIT_BLOCK = 8;
    }

    //ダンジョンの地形情報の設定

    std::vector<std::string> FieldTypeArray;
    std::string fileName = "csv/StageData/DungeonType.csv";
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, FieldTypeArray, 2);

    int FieldTypeNum = stoi(FieldTypeArray[stoi(stage_num) * 2 - 1]);

    switch (FieldTypeNum) {
    case 0:
        ft = "#CAV";
        break;
    case 1:
        ft = "#FST";
        break;
    case 2:
        ft = "#STN";
        break;
    default:
        ft = "#CAV";
        break;
    }
    //ここまで

    _cancelSE.Load("resource/sound/cancelA.wav");
    _cancelSE.SetVolume(200);

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
            auto str = std::string(typeid(*p).name());

            //クリックされたパネルの名前が"AffectObjects"だった場合
            if (str.find("AffectObjects") != NPOS) {
                PanelAffectObjectsFunction(p);
            }
            else if (str.find("Displayer") != NPOS) {
                PanelDisplayerFunction(p);
            }
            else if (str.find("SceneTrans") != NPOS) {

                //ここにスタートからゴールへの経路探索処理を追加する
                if (!Start_Connect_Goal()) {
                    _cancelSE.Play();
                    continue;
                }

                PanelSceneTransFunction(p);

                if (_dungeon != nullptr)
                {
                    _dungeon.reset();
                    _dungeon = nullptr;
                }
                INPUT_MGR->Clear();
                RESOURCE_TABLE->Refresh();

                return new Game(stoi(stage_num));
            }
            else if (str.find("SettingObject") != NPOS) {
                PanelSettingObjectFunction(p);
            }

            p->Update();
        }
    }

    return this;
}

void EditMap::PanelAffectObjectsFunction(std::shared_ptr<PanelBase> panel)
{
    std::vector<std::shared_ptr<PanelBase>> temp_p;

    /*値を変化させる他パネルを検索する*/
    for (auto& ps : PANEL_MGR->_objects) {

        if (ps == nullptr)
            continue;

        auto aff_str = std::string(typeid(*ps).name());
        if (aff_str.find("SettingObject") != NPOS) {
            temp_p.push_back(ps);
        }
    }

    panel->SetSettingObject(temp_p);
    int j = 0;

    auto& obj = PANEL_MGR->_objects;

    for (int i = 0; i < obj.size(); i++) {

        if (obj[i] == nullptr)
            continue;

        auto aff_str = std::string(typeid(*obj[i]).name());
        if (aff_str.find("SettingObject") != NPOS) {
            obj[i] = temp_p[j];
            j++;
        }
    }


    /*値を変化させる他パネルを検索する*/
    //SettingObjectは未選択に
    for (auto& p : PANEL_MGR->_objects) {

        if (p == nullptr)
            continue;

        auto aff_str = std::string(typeid(*p).name());
        if (aff_str.find("SettingObject") != NPOS) {

            std::shared_ptr<PanelSettingObject> psTemp = dynamic_pointer_cast<PanelSettingObject>(p);

            if (psTemp) {
                psTemp->setIsSelected(false);
            }

        }
    }

    selectedObject.reset();

    selectPanelCategory = panel->GetCategoryName();

    if (selectPanelCategory.find("MONSTER") != std::string::npos) {
        _selectCategoryGr.SetDisplayMode(true);
        _selectCategoryGr.SetPosition(Vector2D(panel->GetPosition()._x - 1, panel->GetPosition()._y - 1));
        _selectObjectGr.SetDisplayMode(false);
    }
    else if (selectPanelCategory.find("TRAP") != std::string::npos) {
        _selectCategoryGr.SetDisplayMode(true);
        _selectCategoryGr.SetPosition(Vector2D(panel->GetPosition()._x - 1, panel->GetPosition()._y - 1));
        _selectObjectGr.SetDisplayMode(false);
    }
    else if (selectPanelCategory.find("BLOCK") != std::string::npos) {
        _selectCategoryGr.SetDisplayMode(true);
        _selectCategoryGr.SetPosition(Vector2D(panel->GetPosition()._x - 1, panel->GetPosition()._y - 1));
        _selectObjectGr.SetDisplayMode(false);
    }
    else {
        _selectCategoryGr.SetDisplayMode(false);
        _selectObjectGr.SetDisplayMode(false);
    }

}

void EditMap::PanelDisplayerFunction(std::shared_ptr<PanelBase> panel)
{
}

void EditMap::PanelSceneTransFunction(std::shared_ptr<PanelBase> panel)
{


    std::string filePass = "csv/StageData/";
    std::string fileName = filePass + "EditMapData.csv";

    std::ofstream writing_file;
    writing_file.open(fileName, std::ios::out);


    std::vector<std::string> _stageArray;
    //フィールドの大本となるデータを読み込む
    std::string filename = "csv/StageData/";
    filename += ("map" + stage_num + ".csv");
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + filename, _stageArray);



    TiledVector temp = FIELD->GetFieldSize();

    int countX = 0;
    int countY = 0;

    for (auto data : _stageArray) {
        
        for (int i = 0; i < addTiledObjectList_Trap.size(); i++) {

            if (addTiledObjectList_Trap[i].tiledObject->GetTilePos() == TiledVector(countX, countY)) {

                data = addTiledObjectList_Trap[i].GenerateText;

            }

        }

        for (int i = 0; i < addTiledObjectList_Block.size(); i++) {

            if (addTiledObjectList_Block[i].tiledObject->GetTilePos() == TiledVector(countX, countY)) {

                data = addTiledObjectList_Block[i].GenerateText;

            }

        }


        writing_file << data << std::flush;


        countX++;

        if (countX == temp._x) {
            countX = 0;
            countY++;

            writing_file << std::endl;

            if (countY == temp._y) {
                break;
            }
        }

        if (countX != 0) {
            writing_file << "," << std::flush;
        }

    }

    filePass = "csv/StageData/";
    fileName = filePass + "EditMap_MonsterData.csv";

    std::ofstream writing_file_monster;
    writing_file_monster.open(fileName, std::ios::out);

    writing_file_monster << "hp, attack, defence, magic_attack, magic_defence, speed, startX, startY, name, skill" << std::endl;

    filename = "csv/StageData/monsters";
    filename += (stage_num + ".csv");
    
    std::vector<std::string> dataArray;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + filename, dataArray, 1);

    const int parameterNum = 10;
    countX = 0;

    for (auto data : dataArray) {

        if (data.empty()) {
            break;
        }

        writing_file_monster << data << std::flush;

        countX++;
        
        if (countX == parameterNum) {
            writing_file_monster << std::endl;
            countX = 0;
        }
        else {
            writing_file_monster << "," << std::flush;
        }

    }

    for (int i = 0; i < addTiledObjectList_Monster.size(); i++) {

        writing_file_monster << addTiledObjectList_Monster[i].GenerateText <<std::endl;

    }


}

void EditMap::PanelSettingObjectFunction(std::shared_ptr<PanelBase> panel)
{

    //試験的にダウンキャストを使用
    //まずかったら変えます

    std::shared_ptr<PanelSettingObject> ps = dynamic_pointer_cast<PanelSettingObject>(panel);

    if (ps) {

        if (ps->getPanelObjectName().find("Lv") != NPOS)
            return;

        if (ps->getPanelObjectName().empty())
            return;

        if (ps->getIsSelected()) {
            ps->setIsSelected(false);
            selectedObject.reset();
            _selectObjectGr.SetDisplayMode(false);
        }
        else {
            ps->setIsSelected(true);
            selectedObject = ps;
            _selectObjectGr.SetDisplayMode(true);
            _selectObjectGr.SetPosition(Vector2D(ps->GetPosition()._x - 8, ps->GetPosition()._y - 8));
        }
        
    }
    else {
        return;
    }


    /*値を変化させる他パネルを検索する*/
    //他のSettingObjectは未選択に
    for (auto& p : PANEL_MGR->_objects) {

        if (p == nullptr)
            continue;

        if (p == ps)
            continue;

        auto aff_str = std::string(typeid(*p).name());
        if (aff_str.find("SettingObject") != NPOS) {
            
            std::shared_ptr<PanelSettingObject> psTemp = dynamic_pointer_cast<PanelSettingObject>(p);

            if (psTemp) {
                psTemp->setIsSelected(false);
            }

        }
    }

}

void EditMap::SetPanelInstance(std::string key_name, std::shared_ptr<PanelBase>& panel, PanelContent& temp)
{
    if(key_name == "CHANGE_LIST"){
        panel = std::make_shared<PanelAffectObjects>(temp);
    }else if(key_name == "MOVE"){
        panel = std::make_shared<PanelSceneTransition>(temp);
    }
    else if(key_name == "SELECT_OBJ"){
        panel = std::make_shared<PanelSettingObject>(temp);
    }else if(key_name == "SHOW"){
        panel = std::make_shared<PanelDisplayer>(temp);
    }
}

void EditMap::DebugOutputFile()
{
    std::ofstream writing_file;
    writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::out);
    writing_file.close();
}





void EditMap::SetObject() {

    if (!MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
        return;

    //パネルが選択されているか
    if (!selectedObject)
        return;

    //クリック位置がフィールド内かチェック
    auto cursorPos = MOUSE->GetCursorPos();
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);
    if (!FIELD->IsInside(tiledCursorPos))
        return;


    bool isSetting = SetObjectCheck(tiledCursorPos);


    if (isSetting) {

        if (selectPanelCategory == "MONSTER" && set_count[selectPanelCategory] < LIMIT_MONSTER) {

            std::string fileName = "csv/Edit/MONSTER_DATA/"+selectedObject->getPanelObjectName() + "/Lv1.csv";

            std::string GenerateText = "";

            std::vector<TiledObject*> temp = _dungeon->GenerateMonster(fileName, tiledCursorPos, &GenerateText);

            addTileObject_Monster temp_m;

            for (auto to : temp) {

                to->Init();

                auto aff_str = std::string(typeid(*to).name());
                if (aff_str.find("Monster") != NPOS) {
                    temp_m.MonsterObject = to;
                }else{
                    temp_m.MagicSquareObject = to;
                }
            }

            temp_m.GenerateText = GenerateText;

            addTiledObjectList_Monster.push_back(temp_m);

            FIELD->Setup();
            OBJECT_MGR->Refresh();

            set_count[selectPanelCategory]++;
        }
        else if (selectPanelCategory == "TRAP" && set_count[selectPanelCategory] < LIMIT_TRAP) {
            TiledObject* temp = _dungeon->GenerateAddObject(selectedObject->GenerateText, tiledCursorPos._x, tiledCursorPos._y, cursorPos);
            temp->Init();

            addTileObject atemp;
            atemp.tiledObject = temp;
            atemp.GenerateText = selectedObject->GenerateText;

            addTiledObjectList_Trap.push_back(atemp);
            

            FIELD->SetFieldType(tiledCursorPos, ft);

            FIELD->Setup();
            OBJECT_MGR->Refresh();

            set_count[selectPanelCategory]++;

        }
        else if (selectPanelCategory == "BLOCK" && set_count[selectPanelCategory] < LIMIT_BLOCK) {
            TiledObject* temp = _dungeon->GenerateAddObject(selectedObject->GenerateText, tiledCursorPos._x, tiledCursorPos._y, cursorPos);
            temp->Init();

            addTileObject atemp;
            atemp.tiledObject = temp;
            atemp.GenerateText = selectedObject->GenerateText;

            addTiledObjectList_Block.push_back(atemp);

            

            FIELD->SetFieldType(tiledCursorPos, ft);

            FIELD->Setup();
            OBJECT_MGR->Refresh();

            set_count[selectPanelCategory]++;

        }

    }


}




bool EditMap::SetObjectCheck(TiledVector tiledCursorPos) {

    auto objects = FIELD->GetTiledObjects(tiledCursorPos);

    if (objects.empty()) {
        return true;
    }

    return false;

}



void EditMap::DeleteAddedObject() {

    if (!MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_R))
        return;

    //クリック位置がフィールド内かチェック
    auto cursorPos = MOUSE->GetCursorPos();
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);
    if (!FIELD->IsInside(tiledCursorPos))
        return;

    for (int i = 0; i < addTiledObjectList_Trap.size(); i++) {

        if (addTiledObjectList_Trap[i].tiledObject->GetTilePos() == tiledCursorPos) {

            FIELD->SetRawNumber(addTiledObjectList_Trap[i].tiledObject->GetTilePos(), 0);
            OBJECT_MGR->Remove(addTiledObjectList_Trap[i].tiledObject);
            addTiledObjectList_Trap.erase(addTiledObjectList_Trap.begin() + i);
            OBJECT_MGR->Refresh();

            /****オブジェクト設置数の減算処理ここから****/
            set_count["TRAP"]--;
            /****オブジェクト設置数の減算処理ここまで****/

            
        }

    }

    for (int i = 0; i < addTiledObjectList_Block.size(); i++) {

        if (addTiledObjectList_Block[i].tiledObject->GetTilePos() == tiledCursorPos) {

            FIELD->SetRawNumber(addTiledObjectList_Block[i].tiledObject->GetTilePos(), 0);
            OBJECT_MGR->Remove(addTiledObjectList_Block[i].tiledObject);
            addTiledObjectList_Block.erase(addTiledObjectList_Block.begin() + i);
            OBJECT_MGR->Refresh();


            /****オブジェクト設置数の減算処理ここから****/
            set_count["BLOCK"]--;
            /****オブジェクト設置数の減算処理ここまで****/
        }

    }

    for (int i = 0; i < addTiledObjectList_Monster.size(); i++) {

        if (addTiledObjectList_Monster[i].MagicSquareObject->GetTilePos() == tiledCursorPos) {

            OBJECT_MGR->Remove(addTiledObjectList_Monster[i].MonsterObject);
            OBJECT_MGR->Remove(addTiledObjectList_Monster[i].MagicSquareObject);
            addTiledObjectList_Monster.erase(addTiledObjectList_Monster.begin() + i);
            OBJECT_MGR->Refresh();


            /****オブジェクト設置数の減算処理ここから****/
            set_count["MONSTER"]--;
            /****オブジェクト設置数の減算処理ここまで****/
        }

    }




}

//スタートとゴールがつながっているか
bool EditMap::Start_Connect_Goal() {
    
    ColleagueNotifyer notifyer;
    BattleParameter param(10, 10, 10, 10, 10, 10);
    Enemy* dummy = new Enemy(_dungeon->getStart()->GetTilePos(), param, *_dungeon->getGoal().get(), notifyer, "blaver");

    std::vector<TiledVector> _pathToTarget;

    AstarPathFinder* _astar = new AstarPathFinder(*dummy, _pathToTarget, true);

    std::vector<TiledVector> _pathRef = _astar->GetPathToTarget(_dungeon->getStart()->GetTilePos(), _dungeon->getGoal()->GetTilePos(), 100);

    OBJECT_MGR->Remove(dummy);
    OBJECT_MGR->Refresh();

    if (_pathRef.size() == 0) {
        return false;
    }
    else {
        return true;
    }

}








