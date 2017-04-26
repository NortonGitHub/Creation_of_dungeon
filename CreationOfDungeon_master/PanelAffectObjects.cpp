#include "PanelAffectObjects.h"

#include "PanelSettingObject.h"
#include "PanelDisplayer.h"
#include "cd_666s/Utility/CSVReader.h"
#include "cd_666s/Resources/AllResourceManager.h"

PanelAffectObjects::PanelAffectObjects()
{
}

PanelAffectObjects::~PanelAffectObjects()
{
}

void PanelAffectObjects::Init(PanelContent _panelContent)
{
    panel = _panelContent;
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

void PanelAffectObjects::SetSettingObject(std::vector<PanelBase>& _tps)
{
    CSVReader reader;

    std::string fileName = "csv/Edit/";
    fileName += panel._name + ".csv";
    std::vector<std::string> _array;

    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, _array);

    for (int i = 0; i < _tps.size(); i++) {
        if (i < _array.size()) {
            _tps[i] = PanelSettingObject(_array[i]);
        }
        else {
            _tps[i] = PanelDisplayer();
        }
    }
}

bool PanelAffectObjects::IsClicked()
{
    return GetIsClicked(panel);
}
