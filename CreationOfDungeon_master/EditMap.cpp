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
    //std function �ɕύX����H
    _functions.resize(0);

    //NOTE:
    //�e��UI�Ɏ�ޕʂ̏����i�[���A
    //�܂��ق���UI����̖߂�l����̕ω��ɂ���Ă��̒l��Ԃ�����ύX�����肷��
    //�d�g�݂��l�Ă���K�v������

    std::string _ui_name;

#if 0
    /*�����R�[�h*/
    /*NOTE*/
    /*
        PanelBase�ɂ́A���̃p�l���̖��O�A���W�A�ϐ����i�[����Ă���
        �ϐ��͎q�N���X���ƂɈقȂ�̂Œ���
    */
    std::vector<PanelBase> panels; //�����R�[�h�p

    /*
        �ʂ̃I�u�W�F�N�g�ւ̃A�N�Z�X���K�v�ɂȂ����ۂ�
        �ΏۂƂȂ�I�u�W�F�N�g���i�[����
        �z�� �Ȃ�т� �ȈՊ֐�
    */
    /*multimap �L�[:�J�e�S����, �l:�Ώۂ̃N���X�^�I�u�W�F�N�g*/
    std::multimap<std::string, PanelBase> _targets;
    auto SetClassType = [&](std::string _category) {
        _targets.clear();
        for (auto ps : panels) {
            if (ps.GetCategoryName() == _category) {
                _targets.emplace(_category, ps);
            }
        }
    };
    /*���̏���
    ���Ӗ�����Ȃ��H
     -> ��{�̔z��panels�̒��́A�^���N���XPanelSettingObject
     �̗v�f��PanelContent������������̂�����A
     �������������ł���
    */

    for (auto p : panels) {
        //
        bool isClicked = p.IsClicked();

        //�����̃I�u�W�F�N�g���N���b�N
        //���̃I�u�W�F�N�g�̎��(�N���X)�ɂ����
        //�������e���ω�����B
        //�܂��A�ʂ̃T�u�N���X�̃I�u�W�F�N�g��
        //������


        //�I�u�W�F�N�g���N���b�N���ꂽ��
        if (isClicked) {
            auto str = std::string(typeid(p).name());

            if (str.find("AffectObjects") != std::string::npos) {
#if 0
                std::map<std::string, PanelBase> panel_temps;//��������
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
