#pragma once
#include "SceneBase.h"
#include "MakeDungeon.h"

#include "PanelBase.h"
#include "PanelContent.h"
#include "PanelSettingObject.h"

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

    std::shared_ptr<MakeDungeon> _dungeon;

    std::vector<std::string> _functions;

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



    //エディットで追加したオブジェクトの参照先を表す
    //罠
    std::vector<addTileObject> addTiledObjectList_Trap;
    //ブロック
    std::vector<addTileObject> addTiledObjectList_Block;
    //モンスター
    std::vector<addTileObject_Monster> addTiledObjectList_Monster;


};










