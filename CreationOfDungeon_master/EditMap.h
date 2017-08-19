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


    std::shared_ptr<PanelSettingObject> selectedObject;


};

