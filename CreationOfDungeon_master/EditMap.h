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
    EditMap(std::string _area_num ,string _stage_num);
    ~EditMap();

    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    }

    void Init();

private:
    const size_t NPOS;

    /****上限カウント用****/
    std::map<std::string, int> set_count;
    //int set_count[3];
    /****上限カウント用****/

    //上限設定
    //仮の定数(あとでconstで宣言し直そう)
    int LIMIT_TRAP;
    int LIMIT_MONSTER;
    int LIMIT_BLOCK;

    std::string class_name;

    UIManager _uiManager;

    std::string stage_num;
	std::string stage_num_temp;

	std::string area_num;

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

	void PanelPageChangeObjectFunction(std::shared_ptr<PanelBase> panel);

    void SetPanelInstance(std::string key_name, ::shared_ptr<PanelBase>& panel, PanelContent& temp);

    void DebugOutputFile();

	void ResetCost(std::string selectCategory, std::string ObjectName);



    void SetObject();

    bool SetObjectCheck(TiledVector tiledCursorPos);

    void DeleteAddedObject();


    void GenerateObject(std::string typeName, int countX, int countY);

    bool Start_Connect_Goal();

	int CheckCost(std::string selectPanelCategory, std::string ObjectName);
	int CheckObjectNum(std::string selectPanelCategory, std::string ObjectName);
	int CheckPayOff();

    std::shared_ptr<PanelSettingObject> selectedObject;


    std::string selectPanelCategory;


    struct addTileObject {

		std::string ObjectName;
        TiledObject* tiledObject;
		int Cost;
        std::string GenerateText;

    };

    struct addTileObject_Monster {

		std::string ObjectName;
        TiledObject* MonsterObject;
        TiledObject* MagicSquareObject;
		int Cost;
        std::string GenerateText;

    };



    //エディットで追加したオブジェクトの参照先を表す
    //罠
    std::vector<addTileObject> addTiledObjectList_Trap;
    //ブロック
    std::vector<addTileObject> addTiledObjectList_Block;
    //モンスター
    std::vector<addTileObject_Monster> addTiledObjectList_Monster;

	int payOffCost;
    
    Sound _cancelSE;

    Sprite _selectCategoryGr;
    Sprite _selectObjectGr;

	EditObject editObject;

	//ページ関係
	int pageNum;
	int pageMaxNum;

};










