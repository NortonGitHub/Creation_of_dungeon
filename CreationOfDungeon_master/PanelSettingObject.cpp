#include "PanelSettingObject.h"

#include "cd_666s/Resources/AllResourceManager.h"
#include "cd_666s/Utility/CSVReader.h"


PanelSettingObject::PanelSettingObject()
    : panel()
{
}

PanelSettingObject::PanelSettingObject(PanelContent& _panelContent)
    : panel((_panelContent))
    , _isEnable(true)
{
    _class_name = "SettingObject";
    auto pos = panel._pos;
    _position.Set(pos._x, pos._y);
    Load();
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

void PanelSettingObject::Load()
{
    std::string graph_name;

    //PanelSettingObject‚Ì–¼‘O‚É‚Í"BLOCK","MONSTER","TRAP"‚Ì‚¢‚¸‚ê‚©‚Ì•¶Žš—ñ‚ª“ü‚Á‚Ä‚¢‚é
    if (panel._name.find("SettingObject_") != std::string::npos) {
        graph_name = panel._name.substr(std::string("SettingObject_").length(), panel._name.length());
    }
    else {
        graph_name = panel._name;
    }

    std::string filename = "graph/ui/" + graph_name + ".png";

    _graph.Load(filename);

    _graph.SetPosition(_position);
    _graph.SetDisplayMode(_isEnable);
    _graph.SetPriority(Sprite::Priority::UI);
}

std::string PanelSettingObject::GetCategoryName()
{
    /*
    if (panel._name.find("Monster") != std::string::npos) {
        return "MONSTER";
    }
    else if (panel._name.find("Trap") != std::string::npos) {
        return "TRAP";
    }
    else if (panel._name.find("Block") != std::string::npos) {
        return "BLOCK";
    }
    else {
        return "";
    }
    */
    return _category_name;
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

    writing_file << "name:" << panel._name << " (X,Y):" << panel._pos._x << "," << panel._pos._y << "graph_handle" << _graph.GetResourceHandle() << std::endl;
    writing_file.close();
}