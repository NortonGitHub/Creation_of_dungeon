#include "PanelAffectObjects.h"

#include "PanelSettingObject.h"
#include "PanelDisplayer.h"
#include "cd_666s/Utility/CSVReader.h"
#include "cd_666s/Resources/AllResourceManager.h"

PanelAffectObjects::PanelAffectObjects()
    : panel()
{
}

PanelAffectObjects::PanelAffectObjects(PanelContent& _panelContent)
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

PanelAffectObjects::~PanelAffectObjects()
{
}

void PanelAffectObjects::Init(PanelContent& _panelContent)
{
    panel = _panelContent;
}

void PanelAffectObjects::Update()
{
    GraphicalObject::Update();
}

void PanelAffectObjects::Draw()
{
    GraphicalObject::Draw();
    //    DrawCircle(panel._pos._x, panel._pos._y, 5, GetColor(255, 0, 0));
}

std::string PanelAffectObjects::GetCategoryName()
{
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
}

std::string PanelAffectObjects::GetTypeName()
{
    return panel._name;
}

void PanelAffectObjects::SetSettingObject(std::vector<PanelBase>& _tps)
{
    CSVReader reader;

    std::string fileName = "csv/Edit/";
    fileName += GetCategoryName() + ".csv";
    std::vector<std::string> _array;

    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, _array, 1);
    auto a = _tps.size();
    for (int i = 0; i < _tps.size(); i++) {
        if (i < _array.size()) {
            auto pc = PanelContent(this->panel._pos, _array[i], this->panel._func_var);
            _tps[i].Init(pc); // = PanelSettingObject(pc);//_array[i]);
        }
        else {
            auto pc = PanelContent(this->panel._pos, "none", this->panel._func_var);
            _tps[i].Init(pc);
        }
    }
}

void PanelAffectObjects::DrawDebugPrint()
{
    printfDx("PanelAffectObjects:\n");
    printfDx("name:(%s)  ", panel._name.c_str());
    printfDx("(X:%7.1f, Y:%7.1f)\n", panel._pos._x, panel._pos._y);
    printfDx("-------------------------------\n");

    std::ofstream writing_file;
    writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::app);

    writing_file << "name:" << panel._name << " (X,Y):" << panel._pos._x << "," << panel._pos._y << std::endl;
    writing_file.close();
}

bool PanelAffectObjects::IsClicked()
{
    return GetIsClicked(panel);
}