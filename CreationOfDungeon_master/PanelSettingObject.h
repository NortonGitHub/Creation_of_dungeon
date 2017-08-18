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

private:
    PanelContent panel;

    //���ݕ\������Ă���I�u�W�F�N�g�̖��O
    //Lv���킩��Ȃ��̂łƂ肠����Lv�ɂ��Ă���
    std::string objectName;
};

