#pragma once
#include "SceneBase.h"
#include "MakeDungeon.h"

#include "PanelBase.h"
#include "PanelContent.h"
#include "PanelSettingObject.h"
#include "EditObject.h"
#include "ObjectTextPanel.h"

class EditMap :
    public SceneBase
{
public:
    EditMap(std::string _stage_num);
    ~EditMap();

    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    }

    void Init();

private:
    const size_t NPOS;

    /****����J�E���g�p****/
    std::map<std::string, int> set_count;
    //int set_count[3];
    /****����J�E���g�p****/

    //����ݒ�
    //���̒萔(���Ƃ�const�Ő錾��������)
    int LIMIT_TRAP;
    int LIMIT_MONSTER;
    int LIMIT_BLOCK;

    std::string class_name;

    UIManager _uiManager;

    std::string stage_num;
	std::string stage_num_a;

    std::shared_ptr<MakeDungeon> _dungeon;

    std::vector<std::string> _functions;

	std::shared_ptr<ObjectTextPanel> objectTextPanel;

    //std::vector<std::shared_ptr<PanelBase>> panels;  //UI

    bool IsFirstWave();
    
    SceneBase* PanelFunction();
    void PanelAffectObjectsFunction(std::shared_ptr<PanelBase> panel);
    void PanelDisplayerFunction(std::shared_ptr<PanelBase> panel);
    void PanelSceneTransFunction(std::shared_ptr<PanelBase> panel);
    void PanelSettingObjectFunction(std::shared_ptr<PanelBase> panel);

    void SetPanelInstance(std::string key_name, ::shared_ptr<PanelBase>& panel, PanelContent& temp);

    void DebugOutputFile();




    void SetObject();

    bool SetObjectCheck(TiledVector tiledCursorPos);

    void DeleteAddedObject();


    void GenerateObject(std::string typeName, int countX, int countY);

    bool Start_Connect_Goal();


    std::shared_ptr<PanelSettingObject> selectedObject;


    std::string selectPanelCategory;


    struct addTileObject {

        TiledObject* tiledObject;
        std::string GenerateText;

    };

    struct addTileObject_Monster {

        TiledObject* MonsterObject;
        TiledObject* MagicSquareObject;
        std::string GenerateText;

    };



    //�G�f�B�b�g�Œǉ������I�u�W�F�N�g�̎Q�Ɛ��\��
    //�
    std::vector<addTileObject> addTiledObjectList_Trap;
    //�u���b�N
    std::vector<addTileObject> addTiledObjectList_Block;
    //�����X�^�[
    std::vector<addTileObject_Monster> addTiledObjectList_Monster;

    //�_���W�����̒n�`����ۑ����Ă����i���A�Ȃ�#CAV���j
    std::string ft;


    
    Sound _cancelSE;

    Sprite _selectCategoryGr;
    Sprite _selectObjectGr;

	EditObject editObject;

};










