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

#include "Game.h"

#include "cd_666s/TilebaseAI/MineBomb.h"

#include <typeinfo>
#include <sstream>

#include <iostream>

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
    //std function �ɕύX����H
    _functions.resize(0);

    //NOTE:
    //�e��UI�Ɏ�ޕʂ̏����i�[���A
    //�܂��ق���UI����̖߂�l����̕ω��ɂ���Ă��̒l��Ԃ�����ύX�����肷��
    //�d�g�݂��l�Ă���K�v������

    std::string _ui_name;

#if 1
    /*�����R�[�h*/
    /*NOTE*/
    /*
        PanelBase�ɂ́A���̃p�l���̖��O�A���W�A�ϐ����i�[����Ă���
        �ϐ��͎q�N���X���ƂɈقȂ�̂Œ���
    */
    //std::vector<PanelBase> panels; //�����R�[�h�p

    /*
        �ʂ̃I�u�W�F�N�g�ւ̃A�N�Z�X���K�v�ɂȂ����ۂ�
        �ΏۂƂȂ�I�u�W�F�N�g���i�[����
        �z�� �Ȃ�т� �ȈՊ֐�
    */
    /*multimap �L�[:�J�e�S����, �l:�Ώۂ̃N���X�^�I�u�W�F�N�g*/
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

}

void EditMap::Init()
{
    //�p�l���̓ǂݍ���
    CSVReader reader;
    std::vector<std::string> panels_str;
    std::string filename = "csv/Panel/";
    filename += class_name + ".csv";
    reader.Read(RESOURCE_TABLE->GetFolderPath() + filename, panels_str, 1);

    /*string���e�v�f���Ƃɑ��*/
    /*
    std::map<std::string, std::shared_ptr<PanelBase>> panelTypes;
    panelTypes.insert(std::make_pair("CHANGE_LIST",new PanelAffectObjects()));
    panelTypes.insert(std::make_pair("MOVE", new PanelSceneTransition()));
    panelTypes.insert(std::make_pair("SELECT_OBJ", new PanelSettingObject()));
    panelTypes.insert(std::make_pair("SHOW", new PanelDisplayer()));
    auto b = panelTypes.begin();
    */

    DebugOutputFile();

    //������PANEL_MGR�ǉ�������
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
}

bool EditMap::IsFirstWave()
{
    CSVReader reader;

    std::string filePass = "csv/StageData/";
    std::string fileName = filePass + "template.csv";
    std::vector<std::string> stage_data;

    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, stage_data, 0);
    auto b = stage_data.size();
    //�X�e�[�W�f�[�^������(=��1�E�F�[�u)�̏ꍇ
    if (stage_data.empty()) {
        //template�t�@�C���̐���
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

        //�����̃p�l�����N���b�N�����B
        //���̃p�l���̎��(�N���X)�ɂ����
        //�������e���ω�����B
        //�܂��A�ʂ̃T�u�N���X�̃p�l���̕ϐ���
        //������

        //�p�l�����N���b�N���ꂽ��
        if (isClicked) {
            auto str = std::string(typeid(*p).name());

            //�N���b�N���ꂽ�p�l���̖��O��"AffectObjects"�������ꍇ
            if (str.find("AffectObjects") != NPOS) {
                PanelAffectObjectsFunction(p);
            }
            else if (str.find("Displayer") != NPOS) {
                PanelDisplayerFunction(p);
            }
            else if (str.find("SceneTrans") != NPOS) {
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

    /*�l��ω������鑼�p�l������������*/
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


    /*�l��ω������鑼�p�l������������*/
    //SettingObject�͖��I����
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

    selectPanelCategory = panel->GetCategoryName();

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
    //�t�B�[���h�̑�{�ƂȂ�f�[�^��ǂݍ���
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


}

void EditMap::PanelSettingObjectFunction(std::shared_ptr<PanelBase> panel)
{

    //�����I�Ƀ_�E���L���X�g���g�p
    //�܂���������ς��܂�

    std::shared_ptr<PanelSettingObject> ps = dynamic_pointer_cast<PanelSettingObject>(panel);

    if (ps) {

        if (ps->getPanelObjectName().find("Lv") != NPOS)
            return;

        if (ps->getPanelObjectName().empty())
            return;

        if (ps->getIsSelected()) {
            ps->setIsSelected(false);
            selectedObject.reset();
        }
        else {
            ps->setIsSelected(true);
            selectedObject = ps;
        }
        
    }
    else {
        return;
    }


    /*�l��ω������鑼�p�l������������*/
    //����SettingObject�͖��I����
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
        panel = std::make_shared<PanelDisplayer>();
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

    //�p�l�����I������Ă��邩
    if (!selectedObject)
        return;

    //�N���b�N�ʒu���t�B�[���h�����`�F�b�N
    auto cursorPos = MOUSE->GetCursorPos();
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);
    if (!FIELD->IsInside(tiledCursorPos))
        return;


    bool isSetting = SetObjectCheck(tiledCursorPos);


    if (isSetting) {

        if (selectPanelCategory == "MONSTER") {

        }
        else if (selectPanelCategory == "TRAP") {
            TiledObject* temp = _dungeon->GenerateAddObject(selectedObject->GenerateText, tiledCursorPos._x, tiledCursorPos._y, cursorPos);
            temp->Init();

            addTileObject atemp;
            atemp.tiledObject = temp;
            atemp.GenerateText = selectedObject->GenerateText;

            addTiledObjectList_Trap.push_back(atemp);
            FIELD->Setup();
            OBJECT_MGR->Refresh();
        }
        else if (selectPanelCategory == "BLOCK") {
            TiledObject* temp = _dungeon->GenerateAddObject(selectedObject->GenerateText, tiledCursorPos._x, tiledCursorPos._y, cursorPos);
            temp->Init();

            addTileObject atemp;
            atemp.tiledObject = temp;
            atemp.GenerateText = selectedObject->GenerateText;

            addTiledObjectList_Block.push_back(atemp);
            FIELD->Setup();
            OBJECT_MGR->Refresh();
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

    //�N���b�N�ʒu���t�B�[���h�����`�F�b�N
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
            
        }

    }

    for (int i = 0; i < addTiledObjectList_Block.size(); i++) {

        if (addTiledObjectList_Block[i].tiledObject->GetTilePos() == tiledCursorPos) {

            FIELD->SetRawNumber(addTiledObjectList_Block[i].tiledObject->GetTilePos(), 0);
            OBJECT_MGR->Remove(addTiledObjectList_Block[i].tiledObject);
            addTiledObjectList_Block.erase(addTiledObjectList_Block.begin() + i);
            OBJECT_MGR->Refresh();

        }

    }


}









