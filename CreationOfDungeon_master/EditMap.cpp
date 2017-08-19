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
    //�p�l���̓ǂݍ���
    CSVReader reader;
    std::vector<std::string> panels_str;
    std::string filename = "csv/Panel/";
    filename += class_name + ".csv";
    reader.Read(RESOURCE_TABLE->GetFolderPath() + filename, panels_str, 1);

    DebugOutputFile();

    //������PANEL_MGR�ǉ�������
    int elem_count = 0;
    std::vector<std::string> panel_temp;


    /******�I�u�W�F�N�g�ݒu�p�l�� �t�@�C���ǂݍ��݁@�J�n*******/
    const std::string panel_category[3] = { "BLOCK","MONSTER","TRAP" };

    for (auto panel_c : panel_category) {
        std::string fileName = "csv/Edit/";
        fileName += panel_c + ".csv";
        std::vector<std::string> _array;

        reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, _array, 0);

        int i = 0;
        for (auto f : _array) {
            std::string filename = panel_c + "/" + f;

            Vector2D _pos = Vector2D(std::stoi(panels_str[i]), std::stoi(panels_str[i + 1]));
            //�I��p�̃p�l���̏������������
            auto panelTemp = std::make_shared<PanelSettingObject>(PanelContent(_pos, filename, ""));

            //�I�u�W�F�N�g�ݒu�p�l���̂��ׂẴJ�e�S������map�z��ɑ}��
            _allSettingPanel.insert(std::make_pair(panel_c, panelTemp));
            i += 5;
        }
    }
    /******�I�u�W�F�N�g�ݒu�p�l�� �t�@�C���ǂݍ��݁@�I��*******/

    auto& panel_obj = PANEL_MGR->_objects;

    for (std::string p : panels_str) {
        if (p != "") {
            panel_temp.push_back(p);
            if (elem_count >= 4) {

                try {
                    std::shared_ptr<PanelBase> temp;

                    auto temp2 = PanelContent(Vector2D(std::stoi(panel_temp[0]), std::stoi(panel_temp[1])), panel_temp[2], panel_temp[4]);

                    SetPanelInstance(panel_temp[3], temp, temp2);

                    panel_obj.push_back(temp);
                    panel_obj.back()->Init(temp2);

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

    PanelAffectObjectsFunction("MONSTER");

    std::string file_name = (IsFirstWave() ? "template" : "map" + stage_num);

    for (auto p : PANEL_MGR->_objects) {
        if (p == nullptr)
            continue;
        p->DrawDebugPrint();
    }

    PANEL_MGR->Refresh();

    _dungeon = std::make_shared<MakeDungeon>(stage_num);
    _dungeon->Init(file_name);
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
            auto str = p->GetTypeName();

            //�N���b�N���ꂽ�p�l���̖��O��"AffectObjects"�������ꍇ
            if (str.find("AffectObject") != NPOS) {
                PanelAffectObjectsFunction(p->GetCategoryName());
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

void EditMap::PanelAffectObjectsFunction(std::string category_name)
{
    std::vector<std::shared_ptr<PanelBase>> temp_p;

    using iterator = decltype(_allSettingPanel)::iterator;

    std::pair<iterator, iterator> obj = _allSettingPanel.equal_range(category_name);

    //auto obj = _allSettingPanel.find(category_name)->second;

    /*�l��ω������鑼�p�l������������*/

#if 0
    for (auto p : ps) {
        if (p == nullptr)
            continue;

        auto class_name = p->GetTypeName();

        //�J�e�S���[������v�������̂�p�ɏ㏑������
        if (class_name.find("SettingObject") != NPOS) {
            //temp_p.push_back(*ps);
            //auto b = temp_p.back(); //�e�X�g�p
            /*
            if (obj != _allSettingPanel.end()) {
                p = std::move(obj);
                auto afetr = p;
            }
            */
            temp_p.push_back(p);
        }
    }
#endif

    int elem_num = 0;
    for (iterator it = obj.first; it != obj.second; ++it) {
        //temp_p[elem_num] = std::move(it->second);
        temp_p.push_back(it->second);
        auto t = temp_p.back();
        ++elem_num;
    }

    auto s = temp_p.size();
    auto temp_itr = temp_p.begin();

    auto& ps = PANEL_MGR->_objects;

    for (auto& p : ps) {
        if (p == nullptr)
            continue;

        size_t dis1 = std::distance(temp_p.begin(), temp_itr);


        if (dis1 >= temp_p.size())
            break;
            
        auto class_name = p->GetPanelClassName();

        //�N���X������v�������̂�p�ɏ㏑������
        if (class_name.find("SettingObject") != NPOS) {
            //auto te = std::move(temp_itr);
            p = *temp_itr;
           // p = std::make_shared<PanelBase>(temp_itr);
//            p = std::move(std::make_shared<PanelBase>(temp_itr));
            ++temp_itr;
        }
    }

    PANEL_MGR->Refresh();

    temp_p.shrink_to_fit();
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
        /*NOTE:������Block,Monster,Trap�̂����ꂩ�̗v�f�����鏈������������*/
        /*NOTE:���݃R���X�g���N�^�ɂ���摜�ǂݍ��ݏ�������L�̏�����ɓ����*/
        //_allSettingPanel.push_back(std::make_shared<PanelSettingObject>(temp));
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