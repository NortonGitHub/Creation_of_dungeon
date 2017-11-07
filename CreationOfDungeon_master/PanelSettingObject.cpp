#include "PanelSettingObject.h"

#include "cd_666s/Resources/AllResourceManager.h"
#include "cd_666s/Utility/CSVReader.h"

#include "cd_666s/DebugDraw.h"

PanelSettingObject::PanelSettingObject()
{
}

PanelSettingObject::PanelSettingObject(std::string _panel_name)
{
    panel._name = _panel_name;
}

PanelSettingObject::PanelSettingObject(PanelContent _panelContent)
    : panel(std::move(_panelContent))
{

    if (panel._name.find("Lv") == std::string::npos) {

        std::string filename = "resource/graph/ui/ObjectFrame.png";

        auto pos = panel._pos;

        _position.Set(pos._x, pos._y);

        _graph.Load(filename);

        _graph.SetPosition(_position);

        _graph.SetPriority(Sprite::Priority::UI);
        Vector2D s = _graph.GetSize();
        _graph.SetScale(Vector2D(48 / s._x, 48 / s._y));

        //_graph.SetDisplayMode(true);

        _graph.SetDisplayMode(false);

        objectName = "";

        graphName = "";

        isSelected = false;

    }
    else {

        objectName = "Lv";

        isSelected = false;

    }

}

PanelSettingObject::~PanelSettingObject()
{
}

void PanelSettingObject::SettingObj(PanelContent& pc)
{
    panel = pc;
}

void PanelSettingObject::Update()
{
    GraphicalObject::Update();
}

void PanelSettingObject::Draw()
{
    //panel.Draw();
    //DrawCircle(panel._pos._x, panel._pos._y, 5, GetColor(255, 0, 0));

    GraphicalObject::Draw();

    /*
    if (isSelected) {
        Debug::DrawRectWithPoint(_graph.GetPosition(), _graph.GetPosition() + _graph.GetScale() * _graph.GetSize(), Color4(1, 0, 0, 1), false);
    }
    */

}

void PanelSettingObject::Init(PanelContent& _panelContent)
{
    panel = _panelContent;
}

bool PanelSettingObject::IsClicked()
{
    return GetIsClicked(panel);
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


void PanelSettingObject::PanelSettingObject_SettingPanel(std::string panelName, std::string GenerateText, std::string CategoryName, std::string graphName) {



    if (panel._name.find("Lv") == std::string::npos) {

        if (!panelName.empty()) {

            objectName = panelName;

            this->graphName = graphName;

            this->GenerateText = GenerateText;

            std::string filename;

            if (CategoryName == "MONSTER") {
                filename = "resource/graph/tiledObject/" + this->graphName + ".png";
            }
            else if (CategoryName == "TRAP") {
                filename = "resource/graph/trap/" + this->graphName + ".png";
            }
            else if (CategoryName == "BLOCK") {
                filename = "resource/graph/" + this->graphName + ".png";
            }



            auto pos = panel._pos;

            _position.Set(pos._x, pos._y);

            _graph.Load(filename);

            _graph.SetPosition(_position);
            _graph.SetPriority(Sprite::Priority::UI);

            Vector2D s = _graph.GetSize();
            _graph.SetScale(Vector2D(48 / s._x, 48 / s._y));

            _graph.SetDisplayMode(true);

        }
        else {

            std::string filename = "resource/graph/ui/ObjectFrame.png";

            objectName = panelName;

            this->graphName = graphName;

            this->GenerateText = GenerateText;

            auto pos = panel._pos;

            _position.Set(pos._x, pos._y);

            _graph.Load(filename);

            _graph.SetPosition(_position);

            _graph.SetPriority(Sprite::Priority::UI);
            Vector2D s = _graph.GetSize();
            _graph.SetScale(Vector2D(48 / s._x, 48 / s._y));

            //_graph.SetDisplayMode(true);

            _graph.SetDisplayMode(false);

        }

    }


}


void PanelSettingObject::setIsSelected(bool flag) {

    isSelected = flag;

}


bool PanelSettingObject::getIsSelected() {
    return isSelected;
}

std::string PanelSettingObject::getPanelObjectName() {

    return objectName;

}
