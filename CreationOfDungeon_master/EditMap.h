#pragma once
#include "SceneBase.h"
#include "MakeDungeon.h"

#include "PanelBase.h"
#include "PanelContent.h"

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

    std::vector<std::shared_ptr<PanelBase>> panels;  //UI

    bool IsFirstWave();
    
    SceneBase* PanelFunction();
    void PanelAffectObjectsFunction(PanelBase panel);
    void PanelDisplayerFunction(PanelBase panel);
    void PanelSceneTransFunction(PanelBase panel);
    void PanelSettingObjectFunction(PanelBase panel);

    void SetPanelInstance(std::string key_name, ::shared_ptr<PanelBase>& panel);

};

