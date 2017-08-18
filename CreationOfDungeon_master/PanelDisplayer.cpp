#include "PanelDisplayer.h"

#include<fstream>

#include "cd_666s/Resources/AllResourceManager.h"

PanelDisplayer::PanelDisplayer()
{
}

PanelDisplayer::~PanelDisplayer()
{
}

void PanelDisplayer::Update()
{
    //panel.Update();
    GraphicalObject::Update();
}

void PanelDisplayer::Draw()
{
    //panel.Draw();
    GraphicalObject::Draw();
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
    printfDx("(X:%7.1f, Y:%7.1f)\n", panel._pos._x, panel._pos._y);
    printfDx("-------------------------------\n");

    std::ofstream writing_file;
    writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::app);

    writing_file << "name:" << panel._name << " (X,Y):" << panel._pos._x << "," << panel._pos._y << std::endl;
    writing_file.close();
}
