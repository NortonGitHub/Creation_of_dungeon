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

    void PanelSettingObject_SettingPanel(std::string panelName, std::string GenerateText, std::string CategoryName, std::string graphName);

    void setIsSelected(bool flag);
    bool getIsSelected();

    std::string getPanelObjectName();



    //��������ۂ̃e�L�X�g
    std::string GenerateText;

private:
    PanelContent panel;

    //���ݕ\������Ă���I�u�W�F�N�g�̖��O
    //Lv���킩��Ȃ��̂łƂ肠����Lv�ɂ��Ă���
    std::string objectName;

    std::string graphName;
    

    bool isSelected;

};

