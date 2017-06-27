#include "PanelSceneTransition.h"

#include<fstream>

#include "cd_666s/Utility/CSVReader.h"
#include "cd_666s/Resources/AllResourceManager.h"


PanelSceneTransition::PanelSceneTransition()
    : panel()
{
}

PanelSceneTransition::PanelSceneTransition(PanelContent & _panelContent)
    : panel(std::move(_panelContent))
{
//    panel = std::move(_panelContent);
    std::string filename = "graph/ui/" + panel._name + ".png";

    auto pos = panel._pos;

    _position.Set(pos._x, pos._y);

    _graph.Load(filename);

    _graph.SetPosition(_position);
    _graph.SetPriority(Sprite::Priority::UI);
    //_graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

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

std::string PanelSceneTransition::GetCategoryName()
{
    return panel._name;
}

std::string PanelSceneTransition::GetTypeName()
{
    return panel._name;
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
