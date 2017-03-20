#include "PanelAffectObjects.h"

#include "PanelSettingObject.h"

PanelAffectObjects::PanelAffectObjects()
{
}

PanelAffectObjects::~PanelAffectObjects()
{
}

void PanelAffectObjects::Update()
{
}

void PanelAffectObjects::Draw()
{
}

std::string PanelAffectObjects::GetCategoryName()
{
    if (panel._name.find("MONSTER") != std::string::npos) {
        return "MONSTER";
    }
    else if (panel._name.find("TRAP") != std::string::npos) {
        return "TRAP";
    }
    else if (panel._name.find("BLOCK") != std::string::npos) {
        return "BLOCK";
    }
    else {
        return "";
    }
}

void PanelAffectObjects::SetObject(PanelBase _other_panel)
{
    /*引数のパネルオブジェクトを
    書き換えること*/

    
}
