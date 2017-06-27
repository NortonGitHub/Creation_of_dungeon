#include "PanelSettingObject.h"

#include "cd_666s/Resources/AllResourceManager.h"
#include "cd_666s/Utility/CSVReader.h"


PanelSettingObject::PanelSettingObject()
    : panel()
{
}

PanelSettingObject::PanelSettingObject(PanelContent& _panelContent)
    : panel(std::move(_panelContent))
    , _isEnable(true)
{
 //   panel = std::move(_panelContent);
    auto graph_name(panel._name.substr(std::string("SettingObject_").length(), panel._name.length()));
    std::string filename = "graph/ui/" + graph_name + ".png";

    auto pos = panel._pos;

    _position.Set(pos._x, pos._y);

    _graph.Load(filename);

    _graph.SetPosition(_position);
    _graph.SetDisplayMode(_isEnable);
    _graph.SetPriority(Sprite::Priority::UI);

}


PanelSettingObject::~PanelSettingObject()
{
}

void PanelSettingObject::Update()
{
    GraphicalObject::Update();
}

void PanelSettingObject::Draw()
{
    //panel.Draw();
    //DrawCircle(panel.GetPosition()._x, panel.GetPosition()._y, 5, GetColor(255, 0, 0));
    _graph.SetDisplayMode(_isEnable);
    GraphicalObject::Draw();
}

void PanelSettingObject::Init(PanelContent& _panelContent)
{
    panel = _panelContent;
}

std::string PanelSettingObject::GetTypeName()
{
    return panel._name;
}

bool PanelSettingObject::IsClicked()
{
    return GetIsClicked(panel);
}

bool PanelSettingObject::IsEnable()
{
    return _isEnable;
}

void PanelSettingObject::DrawDebugPrint()
{
    printfDx("PanelSettingObject:\n");
    printfDx("name:(%s)  ", panel._name.c_str());
    printfDx("(X:%7.1f, Y:%7.1f)\n", panel._pos._x, panel._pos._y);
    printfDx("-------------------------------\n");

    std::ofstream writing_file;
    writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::app);

    writing_file << "name:" << panel._name << " (X,Y):" << panel._pos._x << "," << panel._pos._y << std::endl;
    writing_file.close();
}
