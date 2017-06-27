#include "PanelDisplayer.h"

#include<fstream>

#include "cd_666s/Resources/AllResourceManager.h"
#include "cd_666s/Utility/CSVReader.h"

PanelDisplayer::PanelDisplayer()
    : panel()
{
}

PanelDisplayer::PanelDisplayer(PanelContent & _panelContent)
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


PanelDisplayer::~PanelDisplayer()
{
}

void PanelDisplayer::Init(PanelContent & _panelContent)
{
    panel = _panelContent;
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

void PanelDisplayer::SetSettingObject(std::vector<PanelBase>& _tps)
{
}

bool PanelDisplayer::IsClicked()
{
    return GetIsClicked(panel);
}

std::string PanelDisplayer::GetTypeName()
{
    return panel._name;
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
