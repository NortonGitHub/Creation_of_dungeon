#include "PanelSettingObject.h"



PanelSettingObject::PanelSettingObject()
{
}

PanelSettingObject::PanelSettingObject(std::string _panel_name)
{
    panel._name = _panel_name;
}


PanelSettingObject::~PanelSettingObject()
{
}

void PanelSettingObject::SettingObj(PanelContent pc)
{
    panel = pc;
}

void PanelSettingObject::Init(PanelContent _panelContent)
{
    panel = _panelContent;
}

bool PanelSettingObject::IsClicked()
{
    return GetIsClicked(panel);
}
