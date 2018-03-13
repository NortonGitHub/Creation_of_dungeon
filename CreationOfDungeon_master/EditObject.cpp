#include "EditObject.h"
#include "cd_666s\Utility\CSVReader.h"
#include "cd_666s\Resources\AllResourceManager.h"
#include "ShopPanel.h"
#include "ShopAssortment.h"


EditObject::EditObject()
{

	CSVReader reader;

	std::string fileName = "csv/Edit/BLOCK.csv";

	std::vector<std::string> EditObjectArray;

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, EditObjectArray, 1);

	int DataNum = 5;

	for (int j = 0; j < EditObjectArray.size(); j += DataNum) {
		std::shared_ptr<EditOblect_Block> editOblect = make_shared<EditOblect_Block>();

		editOblect->ObjectName = EditObjectArray[j];
		editOblect->ResourceName = EditObjectArray[j + 1];
		editOblect->Cost = std::stoi(EditObjectArray[j + 2]);
		editOblect->IncreaseCost = std::stoi(EditObjectArray[j + 3]);
		editOblect->GenerateText = EditObjectArray[j + 4];

		editOblectBlockList.push_back(editOblect);
	}

	fileName = "csv/Edit/TRAP.csv";

	EditObjectArray.clear();

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, EditObjectArray, 1);

	for (int j = 0; j < EditObjectArray.size(); j += DataNum) {
		std::shared_ptr<EditOblect_Trap> editOblect = make_shared<EditOblect_Trap>();

		editOblect->ObjectName = EditObjectArray[j];
		editOblect->ResourceName = EditObjectArray[j + 1];
		editOblect->Cost = std::stoi(EditObjectArray[j + 2]);
		editOblect->IncreaseCost = std::stoi(EditObjectArray[j + 3]);
		editOblect->GenerateText = EditObjectArray[j + 4];

		editOblect->level = ShopAssortment::getInstance()->getTrapLevel(editOblect->ObjectName);
		editOblect->LevelUpCost = -1;

		editOblectTrapList.push_back(editOblect);
	}

	fileName = "csv/Edit/MONSTER.csv";

	EditObjectArray.clear();

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, EditObjectArray, 1);

	for (int j = 0; j < EditObjectArray.size(); j += DataNum) {
		std::shared_ptr<EditOblect_Monster> editOblect = make_shared<EditOblect_Monster>();

		editOblect->ObjectName = EditObjectArray[j];
		editOblect->ResourceName = EditObjectArray[j + 1];
		editOblect->Cost = std::stoi(EditObjectArray[j + 2]);
		editOblect->IncreaseCost = std::stoi(EditObjectArray[j + 3]);
		editOblect->GenerateInformationPath = EditObjectArray[j + 4];

		editOblect->level = ShopAssortment::getInstance()->getMonsterLevel(editOblect->ObjectName);

		editOblect->LevelUpCost = -1;

		std::string fileNameTemp = "csv/Edit/MONSTER_DATA/" + editOblect->ObjectName + "/LevelUpCost.csv";
		std::vector<std::string> EditObjectArrayTemp;

		reader.Read(RESOURCE_TABLE->GetFolderPath() + fileNameTemp, EditObjectArrayTemp, 1);

		for (int i = 0; i < EditObjectArrayTemp.size(); i += 2) {
			if (EditObjectArrayTemp[i] == "Lv" + std::to_string(editOblect->level) + "-" + std::to_string(editOblect->level + 1)) {
				editOblect->LevelUpCost = std::stoi(EditObjectArrayTemp[i + 1]);
			}
		}

		

		editOblectMonsterList.push_back(editOblect);
	}


	
	auto itb = editOblectBlockList.begin();
	while (itb != editOblectBlockList.end()) {
		if (!ShopAssortment::getInstance()->getCanSetObject((*itb)->ObjectName, ShopPanel::PanelCategory::BLOCK)) {
			itb = editOblectBlockList.erase(itb);
		}
		else ++itb;
	}

	auto itt = editOblectTrapList.begin();
	while (itt != editOblectTrapList.end()) {
		if (!ShopAssortment::getInstance()->getCanSetObject((*itt)->ObjectName, ShopPanel::PanelCategory::TRAP)) {
			itt = editOblectTrapList.erase(itt);
		}
		else ++itt;
	}

	auto itm = editOblectMonsterList.begin();
	while (itm != editOblectMonsterList.end()) {
		if (!ShopAssortment::getInstance()->getCanSetObject((*itm)->ObjectName, ShopPanel::PanelCategory::MONSTER)) {
			itm = editOblectMonsterList.erase(itm);
		}
		else ++itm;
	}

	

}


EditObject::~EditObject()
{
}


std::vector<std::string> EditObject::getEditOblectList(std::string CategoryName) {

	std::vector<std::string> result;
	result.clear();

	if (CategoryName.find("MONSTER") != std::string::npos) {
		for (int i = 0; i < editOblectMonsterList.size(); i++) {
			result.push_back(editOblectMonsterList[i]->ObjectName);
			result.push_back(editOblectMonsterList[i]->ResourceName);
			result.push_back(editOblectMonsterList[i]->GenerateInformationPath);
			result.push_back(std::to_string(editOblectMonsterList[i]->level));
			result.push_back(std::to_string(editOblectMonsterList[i]->LevelUpCost));
		}
		return result;
	}
	else if (CategoryName.find("TRAP") != std::string::npos) {
		for (int i = 0; i < editOblectTrapList.size(); i++) {
			result.push_back(editOblectTrapList[i]->ObjectName);
			result.push_back(editOblectTrapList[i]->ResourceName);
			result.push_back(editOblectTrapList[i]->GenerateText);
			result.push_back(std::to_string(editOblectTrapList[i]->level));
			result.push_back(std::to_string(editOblectTrapList[i]->LevelUpCost));
		}
		return result;
	}
	else if (CategoryName.find("BLOCK") != std::string::npos) {
		for (int i = 0; i < editOblectBlockList.size(); i++) {
			result.push_back(editOblectBlockList[i]->ObjectName);
			result.push_back(editOblectBlockList[i]->ResourceName);
			result.push_back(editOblectBlockList[i]->GenerateText);
			result.push_back(std::to_string(-1));
			result.push_back(std::to_string(-1));
		}
		return result;
	}

	return result;

}


void EditObject::ResetLevel() {

	CSVReader reader;

	for (int j = 0; j < editOblectTrapList.size(); j += 1) {
		editOblectTrapList[j]->level = ShopAssortment::getInstance()->getTrapLevel(editOblectTrapList[j]->ObjectName);
		editOblectTrapList[j]->LevelUpCost = -1;
	}

	for (int j = 0; j < editOblectMonsterList.size(); j += 1) {
		
		editOblectMonsterList[j]->level = ShopAssortment::getInstance()->getMonsterLevel(editOblectMonsterList[j]->ObjectName);

		editOblectMonsterList[j]->LevelUpCost = -1;

		std::string fileNameTemp = "csv/Edit/MONSTER_DATA/" + editOblectMonsterList[j]->ObjectName + "/LevelUpCost.csv";
		std::vector<std::string> EditObjectArrayTemp;

		reader.Read(RESOURCE_TABLE->GetFolderPath() + fileNameTemp, EditObjectArrayTemp, 1);

		for (int i = 0; i < EditObjectArrayTemp.size(); i += 2) {
			if (EditObjectArrayTemp[i] == "Lv" + std::to_string(editOblectMonsterList[j]->level) + "-" + std::to_string(editOblectMonsterList[j]->level + 1)) {
				editOblectMonsterList[j]->LevelUpCost = std::stoi(EditObjectArrayTemp[i + 1]);
			}
		}
	}

}

int EditObject::GetCost(std::string CategoryName, std::string objectName) {

	
	if (CategoryName.find("MONSTER") != std::string::npos) {
		for (int i = 0; i < editOblectMonsterList.size(); i++) {
			if (editOblectMonsterList[i]->ObjectName == objectName) {
				return editOblectMonsterList[i]->Cost;
			}
		}
	}
	else if (CategoryName.find("TRAP") != std::string::npos) {
		for (int i = 0; i < editOblectTrapList.size(); i++) {
			if (editOblectTrapList[i]->ObjectName == objectName) {
				return editOblectTrapList[i]->Cost;
			}
		}
	}
	else if (CategoryName.find("BLOCK") != std::string::npos) {
		for (int i = 0; i < editOblectBlockList.size(); i++) {
			if (editOblectBlockList[i]->ObjectName == objectName) {
				return editOblectBlockList[i]->Cost;
			}
		}
	}

	return -1;

}

int EditObject::GetIncreaseCost(std::string CategoryName, std::string objectName) {


	if (CategoryName.find("MONSTER") != std::string::npos) {
		for (int i = 0; i < editOblectMonsterList.size(); i++) {
			if (editOblectMonsterList[i]->ObjectName == objectName) {
				return editOblectMonsterList[i]->IncreaseCost;
			}
		}
	}
	else if (CategoryName.find("TRAP") != std::string::npos) {
		for (int i = 0; i < editOblectTrapList.size(); i++) {
			if (editOblectTrapList[i]->ObjectName == objectName) {
				return editOblectTrapList[i]->IncreaseCost;
			}
		}
	}
	else if (CategoryName.find("BLOCK") != std::string::npos) {
		for (int i = 0; i < editOblectBlockList.size(); i++) {
			if (editOblectBlockList[i]->ObjectName == objectName) {
				return editOblectBlockList[i]->IncreaseCost;
			}
		}
	}

	return -1;

}


int EditObject::GetEditObjectNum(std::string CategoryName) {

	if (CategoryName.find("MONSTER") != std::string::npos) {
		return editOblectMonsterList.size();
	}
	else if (CategoryName.find("TRAP") != std::string::npos) {
		return editOblectTrapList.size();
	}
	else if (CategoryName.find("BLOCK") != std::string::npos) {
		return editOblectBlockList.size();
	}

	return -1;

}





