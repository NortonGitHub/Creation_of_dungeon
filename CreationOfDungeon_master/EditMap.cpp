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
    //std function �ɕύX����H
    _functions.resize(0);

    //NOTE:
    //�e��UI�Ɏ�ޕʂ̏����i�[���A
    //�܂��ق���UI����̖߂�l����̕ω��ɂ���Ă��̒l��Ԃ�����ύX�����肷��
    //�d�g�݂��l�Ă���K�v������

    std::string _ui_name;

#if 1
    /*NOTE*/
    /*
        PanelBase�ɂ́A���̃p�l���̖��O�A���W�A�ϐ����i�[����Ă���
        �ϐ��͎q�N���X���ƂɈقȂ�̂Œ���
    */
    std::vector<PanelBase> panels; //�����R�[�h�p

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
