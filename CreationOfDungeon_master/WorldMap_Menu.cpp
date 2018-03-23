#include "WorldMap_Menu.h"

#include "EditMap.h"
#include "FunctionTransScene.h"
#include "PanelBase.h"

#include "PanelAffectObjects.h"
#include "PanelDisplayer.h"
#include "PanelSceneTransition.h"
#include "PanelSettingObject.h"
#include "PanelPageChangeObject.h"

#include "cd_666s/Utility/CSVReader.h"
#include "cd_666s/Resources/AllResourceManager.h"

#include "PanelObjectManager.h"

#include "cd_666s/TilebaseAI/TileField.h"
#include "cd_666s/TilebaseAI/TiledObjectMnager.h"

#include "cd_666s/DebugDraw.h"

#include "Game.h"

#include "cd_666s\TilebaseAI\Enemy.h"
#include "cd_666s\TilebaseAI\AI\AstarPathFinder.h"

#include <typeinfo>
#include <sstream>

#include <iostream>

#include <assert.h>

#include "ShopAssortment.h"
#include "MoneyManager.h"

#define STR(var) #var


WorldMap_Menu::WorldMap_Menu()
	:NPOS(std::string::npos)
{

	_functions.reserve(20);
	//panels.reserve(30);
	class_name = "worldmap";

	_selectCategoryGr.Load("resource/graph/ui/SelectTypeFrame.png");
	_selectCategoryGr.SetPriority(static_cast<int>(Sprite::Priority::UI) + 100);

	_selectCategoryGr.SetDisplayMode(false);

	_selectObjectGr.Load("resource/graph/ui/SelectObjectFrame.png");
	_selectObjectGr.SetPriority(static_cast<int>(Sprite::Priority::UI) + 100);

	_selectObjectGr.SetDisplayMode(false);

	Init();

}


WorldMap_Menu::~WorldMap_Menu()
{
	_functions.clear();

	PANEL_MGR->Clear();

	PANEL_MGR->Refresh();
}

void WorldMap_Menu::Update()
{

	if (!isActive) {
		return;
	}

	_functions.resize(0);



	PanelFunction();


	for (auto p : PANEL_MGR->_objects) {
		if (p != nullptr)
			p->Update();
	}

	if (objectTextPanel->EvolCheck()) {
		std::shared_ptr<PanelSettingObject> temp = selectedObject;
		ShopAssortment::getInstance()->EvolMonster(selectedObject);
		editObject.ResetLevel();
		for (auto p : PANEL_MGR->_objects) {

			if (p == nullptr)
				continue;

			auto str = std::string(typeid(*p).name());

			//クリックされたパネルの名前が"AffectObjects"だった場合
			if (str.find("AffectObjects") != NPOS) {
				if (selectPanelCategory == p->GetCategoryName()) {
					PanelAffectObjectsFunction(p);
				}
			}

		}
		selectedObject = temp;
		_selectCategoryGr.SetDisplayMode(true);
		objectTextPanel->SetMessage(selectedObject);
	}

}


void WorldMap_Menu::Draw()
{

	if (!isActive) {
		return;
	}

	for (auto& p : PANEL_MGR->_objects) {
		if (p != nullptr)
			p->Draw();
	}

	PANEL_MGR->Refresh();

	std::string debugStr = "所持金：" + std::to_string(MoneyManager::getInstance()->getMoney()) + "M\n";

	Debug::DrawString(Vector2D(980, 140), debugStr, Color4(0, 0, 0, 0), 16);



	std::string pageStr = "";

	if (selectPanelCategory.find("MONSTER") != std::string::npos) {
		pageStr += std::to_string(pageNum) + "/" + std::to_string(pageMaxNum);
	}
	else if (selectPanelCategory.find("TRAP") != std::string::npos) {
		pageStr += std::to_string(pageNum) + "/" + std::to_string(pageMaxNum);
	}
	else if (selectPanelCategory.find("BLOCK") != std::string::npos) {
		pageStr += std::to_string(pageNum) + "/" + std::to_string(pageMaxNum);
	}
	else {
		pageStr += std::to_string(pageNum) + "/" + std::to_string(pageMaxNum);
	}

	Debug::DrawString(Vector2D(1055, 270), pageStr, Color4(0, 0, 0, 0), 40);

	objectTextPanel->Draw();

}

void WorldMap_Menu::Init()
{
	//パネルの読み込み
	CSVReader reader;
	std::vector<std::string> panels_str;
	std::string filename = "csv/Panel/";
	filename += class_name + ".csv";
	reader.Read(RESOURCE_TABLE->GetFolderPath() + filename, panels_str, 1);

	/*stringを各要素ごとに代入*/
	/*
	std::map<std::string, std::shared_ptr<PanelBase>> panelTypes;
	panelTypes.insert(std::make_pair("CHANGE_LIST",new PanelAffectObjects()));
	panelTypes.insert(std::make_pair("MOVE", new PanelSceneTransition()));
	panelTypes.insert(std::make_pair("SELECT_OBJ", new PanelSettingObject()));
	panelTypes.insert(std::make_pair("SHOW", new PanelDisplayer()));
	auto b = panelTypes.begin();
	*/

	//DebugOutputFile();

	//ここにPANEL_MGR追加処理を
	int elem_count = 0;
	std::vector<std::string> panel_temp;
	std::vector<PanelContent> panel_cont_temp(1);
	panel_cont_temp.reserve(30);

	auto& panel_obj = PANEL_MGR->_objects;

	for (std::string p : panels_str) {
		if (p != "") {
			panel_temp.push_back(p);
			if (elem_count >= 4) {

				try {
					std::shared_ptr<PanelBase> temp;

					auto temp2 = std::make_shared<PanelContent>(Vector2D(std::stoi(panel_temp[0]), std::stoi(panel_temp[1])), panel_temp[2], panel_temp[4]);

					SetPanelInstance(panel_temp[3], temp, *temp2);

					panel_obj.push_back(temp);

					//panel_cont_temp.push_back(PanelContent(
					//Vector2D(std::stoi(panel_temp[0]), std::stoi(panel_temp[1])), panel_temp[2], panel_temp[4]));
				}
				catch (std::out_of_range&) {
					assert("Cannot push_back panel elem");
				}
				panel_temp.clear();
				elem_count = 0;
			}
			else {
				elem_count++;
			}
		}
	}

	PANEL_MGR->Refresh();


	panel_cont_temp.clear();

	selectedObject.reset();

	selectPanelCategory = "";

	_cancelSE.Load("resource/sound/cancelA.wav");
	_cancelSE.SetVolume(200);

	objectTextPanel = std::make_shared<ObjectTextPanel>(class_name);

	pageNum = 0;
	pageMaxNum = 0;

	isActive = false;

}

void WorldMap_Menu::SetActive(bool flag)
{

	isActive = flag;


	objectTextPanel->SetActive(flag);

	for (auto& p : PANEL_MGR->_objects) {
		if (p != nullptr)
			p->SetActive(flag);
	}

	if (selectPanelCategory == "") {
		_selectCategoryGr.SetDisplayMode(false);
	}
	else {
		_selectCategoryGr.SetDisplayMode(flag);
	}
	
	


	selectedObject.reset();

	_selectObjectGr.SetDisplayMode(false);

	if (editObject.GetEditObjectNum(selectPanelCategory) == 0) {
		pageNum = 0;
		pageMaxNum = 0;
	}
	else {
		pageNum = 1;
		pageMaxNum = (editObject.GetEditObjectNum(selectPanelCategory) - 1) / 9 + 1;
	}

}

bool WorldMap_Menu::GetIsActive()
{
	return isActive;
}

void WorldMap_Menu::PanelFunction()
{

	for (auto p : PANEL_MGR->_objects) {

		if (p == nullptr)
			continue;

		//
		bool isClicked = p->IsClicked();

		//何かのパネルがクリックされる。
		//そのパネルの種類(クラス)によって
		//処理内容が変化する。
		//また、別のサブクラスのパネルの変数に
		//干渉する

		//パネルがクリックされたら
		if (isClicked) {
			auto str = std::string(typeid(*p).name());

			//クリックされたパネルの名前が"AffectObjects"だった場合
			if (str.find("AffectObjects") != NPOS) {
				PanelAffectObjectsFunction(p);
			}
			else if (str.find("Displayer") != NPOS) {
				PanelDisplayerFunction(p);
			}
			else if (str.find("SettingObject") != NPOS) {
				PanelSettingObjectFunction(p);
			}
			else if (str.find("PanelPageChangeObject") != NPOS) {
				PanelPageChangeObjectFunction(p);
			}

			p->Update();
		}

	}
}

void WorldMap_Menu::PanelAffectObjectsFunction(std::shared_ptr<PanelBase> panel)
{
	std::vector<std::shared_ptr<PanelBase>> temp_p;

	/*値を変化させる他パネルを検索する*/
	for (auto& ps : PANEL_MGR->_objects) {

		if (ps == nullptr)
			continue;

		auto aff_str = std::string(typeid(*ps).name());
		if (aff_str.find("SettingObject") != NPOS) {
			temp_p.push_back(ps);
		}
	}


	std::shared_ptr<PanelAffectObjects> ps = dynamic_pointer_cast<PanelAffectObjects>(panel);
	ps->SetSettingObject(temp_p, editObject);
	int j = 0;

	auto& obj = PANEL_MGR->_objects;

	for (int i = 0; i < obj.size(); i++) {

		if (obj[i] == nullptr)
			continue;

		auto aff_str = std::string(typeid(*obj[i]).name());
		if (aff_str.find("SettingObject") != NPOS) {
			obj[i] = temp_p[j];
			j++;
		}
	}


	/*値を変化させる他パネルを検索する*/
	//SettingObjectは未選択に
	for (auto& p : PANEL_MGR->_objects) {

		if (p == nullptr)
			continue;

		auto aff_str = std::string(typeid(*p).name());
		if (aff_str.find("SettingObject") != NPOS) {

			std::shared_ptr<PanelSettingObject> psTemp = dynamic_pointer_cast<PanelSettingObject>(p);

			if (psTemp) {
				psTemp->setIsSelected(false);
			}

		}
	}

	selectedObject.reset();

	selectPanelCategory = panel->GetCategoryName();

	if (selectPanelCategory.find("MONSTER") != std::string::npos) {
		_selectCategoryGr.SetDisplayMode(true);
		_selectCategoryGr.SetPosition(Vector2D(panel->GetPosition()._x - 1, panel->GetPosition()._y - 1));
		_selectObjectGr.SetDisplayMode(false);
	}
	else if (selectPanelCategory.find("TRAP") != std::string::npos) {
		_selectCategoryGr.SetDisplayMode(true);
		_selectCategoryGr.SetPosition(Vector2D(panel->GetPosition()._x - 1, panel->GetPosition()._y - 1));
		_selectObjectGr.SetDisplayMode(false);
	}
	else if (selectPanelCategory.find("BLOCK") != std::string::npos) {
		_selectCategoryGr.SetDisplayMode(true);
		_selectCategoryGr.SetPosition(Vector2D(panel->GetPosition()._x - 1, panel->GetPosition()._y - 1));
		_selectObjectGr.SetDisplayMode(false);
	}
	else {
		_selectCategoryGr.SetDisplayMode(false);
		_selectObjectGr.SetDisplayMode(false);
	}

	objectTextPanel->ResetMessage();

	if (editObject.GetEditObjectNum(selectPanelCategory) == 0) {
		pageNum = 0;
		pageMaxNum = 0;
	}
	else {
		pageNum = 1;
		pageMaxNum = (editObject.GetEditObjectNum(selectPanelCategory) - 1) / 9 + 1;
	}


}

void WorldMap_Menu::PanelDisplayerFunction(std::shared_ptr<PanelBase> panel)
{
}



void WorldMap_Menu::PanelSettingObjectFunction(std::shared_ptr<PanelBase> panel)
{

	//試験的にダウンキャストを使用
	//まずかったら変えます

	std::shared_ptr<PanelSettingObject> ps = dynamic_pointer_cast<PanelSettingObject>(panel);

	if (ps) {

		if (ps->getPanelObjectName().find("Lv") != NPOS)
			return;

		if (ps->getPanelObjectName().empty())
			return;

		if (ps->getIsSelected()) {
			ps->setIsSelected(false);
			selectedObject.reset();
			_selectObjectGr.SetDisplayMode(false);
			objectTextPanel->ResetMessage();
		}
		else {
			ps->setIsSelected(true);
			selectedObject = ps;
			_selectObjectGr.SetDisplayMode(true);
			_selectObjectGr.SetPosition(Vector2D(ps->GetPosition()._x - 8, ps->GetPosition()._y - 8));

			objectTextPanel->SetMessage(selectedObject);

		}

	}
	else {
		return;
	}


	/*値を変化させる他パネルを検索する*/
	//他のSettingObjectは未選択に
	for (auto& p : PANEL_MGR->_objects) {

		if (p == nullptr)
			continue;

		if (p == ps)
			continue;

		auto aff_str = std::string(typeid(*p).name());
		if (aff_str.find("SettingObject") != NPOS) {

			std::shared_ptr<PanelSettingObject> psTemp = dynamic_pointer_cast<PanelSettingObject>(p);

			if (psTemp) {
				psTemp->setIsSelected(false);
			}

		}
	}

}


void WorldMap_Menu::PanelPageChangeObjectFunction(std::shared_ptr<PanelBase> panel) {




	std::vector<std::shared_ptr<PanelBase>> temp_p;

	/*値を変化させる他パネルを検索する*/
	for (auto& ps : PANEL_MGR->_objects) {

		if (ps == nullptr)
			continue;

		auto aff_str = std::string(typeid(*ps).name());
		if (aff_str.find("SettingObject") != NPOS) {
			temp_p.push_back(ps);
		}
	}


	std::shared_ptr<PanelPageChangeObject> ps = dynamic_pointer_cast<PanelPageChangeObject>(panel);

	if (ps->IsPageUP()) {
		pageNum++;
	}
	else {
		pageNum--;
	}

	if (pageNum < 1) {
		pageNum = 1;
	}
	else if (pageNum > pageMaxNum) {
		pageNum = pageMaxNum;
	}

	ps->SetSettingObject(temp_p, editObject, selectPanelCategory, pageNum);
	int j = 0;

	auto& obj = PANEL_MGR->_objects;

	for (int i = 0; i < obj.size(); i++) {

		if (obj[i] == nullptr)
			continue;

		auto aff_str = std::string(typeid(*obj[i]).name());
		if (aff_str.find("SettingObject") != NPOS) {
			obj[i] = temp_p[j];
			j++;
		}
	}


	/*値を変化させる他パネルを検索する*/
	//SettingObjectは未選択に
	for (auto& p : PANEL_MGR->_objects) {

		if (p == nullptr)
			continue;

		auto aff_str = std::string(typeid(*p).name());
		if (aff_str.find("SettingObject") != NPOS) {

			std::shared_ptr<PanelSettingObject> psTemp = dynamic_pointer_cast<PanelSettingObject>(p);

			if (psTemp) {
				psTemp->setIsSelected(false);
			}

		}
	}

	selectedObject.reset();

	if (selectPanelCategory.find("MONSTER") != std::string::npos) {
		_selectObjectGr.SetDisplayMode(false);
	}
	else if (selectPanelCategory.find("TRAP") != std::string::npos) {
		_selectObjectGr.SetDisplayMode(false);
	}
	else if (selectPanelCategory.find("BLOCK") != std::string::npos) {
		_selectObjectGr.SetDisplayMode(false);
	}
	else {
		_selectCategoryGr.SetDisplayMode(false);
		_selectObjectGr.SetDisplayMode(false);
	}

	objectTextPanel->ResetMessage();

}







void WorldMap_Menu::SetPanelInstance(std::string key_name, std::shared_ptr<PanelBase>& panel, PanelContent& temp)
{
	if (key_name == "CHANGE_LIST") {
		panel = std::make_shared<PanelAffectObjects>(temp);
	}
	else if (key_name == "MOVE") {
		panel = std::make_shared<PanelSceneTransition>(temp);
	}
	else if (key_name == "SELECT_OBJ") {
		panel = std::make_shared<PanelSettingObject>(temp);
	}
	else if (key_name == "SHOW") {
		panel = std::make_shared<PanelDisplayer>(temp);
	}
	else if (key_name == "PAGE_CHANGE") {
		panel = std::make_shared<PanelPageChangeObject>(temp);
	}
}

void WorldMap_Menu::DebugOutputFile()
{
	std::ofstream writing_file;
	writing_file.open(RESOURCE_TABLE->GetFolderPath() + "test.csv", std::ios::out);
	writing_file.close();
}

