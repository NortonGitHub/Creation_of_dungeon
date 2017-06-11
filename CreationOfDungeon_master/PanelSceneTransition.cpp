#include "PanelSceneTransition.h"

#include<fstream>

#include "cd_666s/Resources/AllResourceManager.h"


PanelSceneTransition::PanelSceneTransition()
{
}


PanelSceneTransition::~PanelSceneTransition()
{
}

void PanelSceneTransition::Update()
{
    GraphicalObject::Update();
}

void PanelSceneTransition::Draw()
{
    GraphicalObject::Draw();
}

void PanelSceneTransition::Init(PanelContent& _panelContent)
{
    panel = _panelContent;
}

bool PanelSceneTransition::IsClicked()
{
    return GetIsClicked(panel);
}

void PanelSceneTransition::DrawDebugPrint()
{
    printfDx("PanelSceneTransition:\n");
    printfDx("name:(%s)  ", panel._name.c_str());
    printfDx("(X:%7.1f, Y:%7.1f)\n", panel._pos._x, panel._pos._y);
    printfDx("-------------------------------\n");

    std::ofstream writing_file;
    writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::app);

    writing_file << "name:" << panel._name << " (X,Y):" << panel._pos._x << "," << panel._pos._y << std::endl;
    writing_file.close();
}
