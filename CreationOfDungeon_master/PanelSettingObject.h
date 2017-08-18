#pragma once
#include "PanelBase.h"
class PanelSettingObject :
    public PanelBase
{
public:
    PanelSettingObject();
    PanelSettingObject(std::string _panel_name);
    PanelSettingObject(PanelContent _panelContent);
    ~PanelSettingObject();

    void SettingObj(PanelContent& pc);

    void Update() override;
    void Draw() override;

    void Init(PanelContent& _panelContent);

    bool IsClicked();

    void DrawDebugPrint() override;

    void PanelSettingObject_SettingPanel(std::string panelName, std::string CategoryName);

    void setIsSelected(bool flag);
    bool getIsSelected();

private:
    PanelContent panel;

    //現在表示されているオブジェクトの名前
    //LvがわからないのでとりあえずLvにしておく
    std::string objectName;

    bool isSelected;

};

