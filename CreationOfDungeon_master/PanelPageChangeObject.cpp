#include "PanelPageChangeObject.h"

#include "PanelSettingObject.h"
#include "PanelDisplayer.h"
#include "cd_666s/Utility/CSVReader.h"
#include "cd_666s/Resources/AllResourceManager.h"


PanelPageChangeObject::PanelPageChangeObject()
	: panel(PanelContent())
{
}

PanelPageChangeObject::PanelPageChangeObject(PanelContent _panelContent)
	: panel(std::move(_panelContent))
{
	std::string filename = "resource/graph/ui/" + panel._name + ".png";


	auto pos = panel._pos;

	_position.Set(pos._x, pos._y);

	_graph.Load(filename);

	_graph.SetPosition(_position);

	_graph.SetPriority(Sprite::Priority::UI);
	//_graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

	//_graph.SetDisplayMode(true);

}


PanelPageChangeObject::~PanelPageChangeObject()
{
}


void PanelPageChangeObject::Init(PanelContent _panelContent)
{
	panel = _panelContent;
}

void PanelPageChangeObject::Update()
{
	GraphicalObject::Update();
}

void PanelPageChangeObject::Draw()
{
	GraphicalObject::Draw();

	//DrawCircle(panel._pos._x, panel._pos._y, 5, GetColor(255, 0, 0));

}

void PanelPageChangeObject::SetSettingObject(std::vector<std::shared_ptr<PanelBase>> _tps, EditObject editObject, std::string CategoryName, int pageNum)
{

	std::vector<std::string> _array;

	_array = editObject.getEditOblectList(CategoryName);

	int DataNum = 0;

	if (CategoryName == "MONSTER") {
		DataNum = 5;
	}
	else if (CategoryName == "TRAP") {
		DataNum = 5;
	}
	else if (CategoryName == "BLOCK") {
		DataNum = 5;
	}
	else {
		return;
	}

	if (pageNum == 0) {
		return;
	}

	if (_array.size() > (pageNum - 1) * 9 * DataNum) {
		_array.erase(_array.begin(), _array.begin() + (pageNum - 1) * 9 * DataNum);
	}

	for (int i = 0; i < _tps.size(); i++) {

		std::shared_ptr<PanelSettingObject> _ps = dynamic_pointer_cast<PanelSettingObject>(_tps[i]);

		if (!_array.empty()) {
			if (_array.size() >= DataNum) {

				_ps->PanelSettingObject_SettingPanel(_array[0], _array[2], CategoryName, _array[1], std::stoi(_array[3]), std::stoi(_array[4]));
				//_tps[i] = PanelSettingObject(_array[i]);
				_array.erase(_array.begin(), _array.begin() + DataNum);
			}
			else {
				_array.clear();
				_ps->PanelSettingObject_SettingPanel("", "", CategoryName, "", -1, -1);
				//_tps[i] = std::make_shared<PanelSettingObject>(nullptr);
			}

		}
		else {
			_ps->PanelSettingObject_SettingPanel("", "", CategoryName, "", -1, -1);
			//_tps[i] = std::make_shared<PanelSettingObject>(nullptr);
		}
	}
}

void PanelPageChangeObject::DrawDebugPrint()
{
	printfDx("PanelPageChangeObject:\n");
	printfDx("name:(%s)  ", panel._name.c_str());
	printfDx("(X:%7.1f, Y:%7.1f)\n", panel._pos._x, panel._pos._y);
	printfDx("-------------------------------\n");

	std::ofstream writing_file;
	writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::app);

	writing_file << "name:" << panel._name << " (X,Y):" << panel._pos._x << "," << panel._pos._y << std::endl;
	writing_file.close();
}

bool PanelPageChangeObject::IsClicked()
{
	return GetIsClicked(panel);
}

bool PanelPageChangeObject::IsPageUP() {

	if (panel._name.find("Left") != std::string::npos) {
		return false;
	}
	else if (panel._name.find("Right") != std::string::npos) {
		return true;
	}
		
	return false;

}

