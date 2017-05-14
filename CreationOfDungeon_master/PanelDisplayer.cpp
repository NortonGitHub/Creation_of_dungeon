#include "PanelDisplayer.h"

#include<fstream>

#include "cd_666s/Resources/AllResourceManager.h"

PanelDisplayer::PanelDisplayer()
{
}


PanelDisplayer::~PanelDisplayer()
{
}

void PanelDisplayer::Init(PanelContent _panelContent)
{
    panel = _panelContent;
}

bool PanelDisplayer::IsClicked()
{
    return GetIsClicked(panel);
}

void PanelDisplayer::DrawDebugPrint()
{
    printfDx("PanelDisplayer:\n");
    printfDx("name:(%s)  ", panel._name.c_str());
    printfDx("(X:%7.1f, Y:%7.1f)\n", panel.GetPosition()._x, panel.GetPosition()._y);
    printfDx("-------------------------------\n");

    std::ofstream writing_file;
    writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::app);

    writing_file << "name:" << panel._name << " (X,Y):" << panel.GetPosition()._x << "," << panel.GetPosition()._y << std::endl;
    writing_file.close();
}
