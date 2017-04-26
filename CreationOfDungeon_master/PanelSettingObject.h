#pragma once
#include "PanelBase.h"
class PanelSettingObject :
    public PanelBase
{
public:
    PanelSettingObject();
    PanelSettingObject(std::string _panel_name);
    ~PanelSettingObject();

    void SettingObj(PanelContent pc);

    void Init(PanelContent _panelContent);

    bool IsClicked();

private:
    PanelContent panel;
};
