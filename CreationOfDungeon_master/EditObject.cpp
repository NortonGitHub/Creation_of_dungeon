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

	for (int j = 0; j < EditObjectArray.size(); j += 3) {
		std::shared_ptr<EditOblect_Block> editOblect = make_shared<EditOblect_Block>();

		editOblect->ObjectName = EditObjectArray[j];
		editOblect->ResourceName = EditObjectArray[j + 1];
		editOblect->GenerateText = EditObjectArray[j + 2];

		editOblectBlockList.push_back(editOblect);
	}

	fileName = "csv/Edit/TRAP.csv";

	EditObjectArray.clear();

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, EditObjectArray, 1);

	for (int j = 0; j < EditObjectArray.size(); j += 3) {
		std::shared_ptr<EditOblect_Trap> editOblect = make_shared<EditOblect_Trap>();

		editOblect->ObjectName = EditObjectArray[j];
		editOblect->ResourceName = EditObjectArray[j + 1];
		editOblect->GenerateText = EditObjectArray[j + 2];

		editOblectTrapList.push_back(editOblect);
	}

	fileName = "csv/Edit/MONSTER.csv";

	EditObjectArray.clear();

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, EditObjectArray, 1);

	for (int j = 0; j < EditObjectArray.size(); j += 3) {
		std::shared_ptr<EditOblect_Monster> editOblect = make_shared<EditOblect_Monster>();

		editOblect->ObjectName = EditObjectArray[j];
		editOblect->ResourceName = EditObjectArray[j + 1];
		editOblect->GenerateInformationPath = EditObjectArray[j + 2];

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
		}
		return result;
	}
	else if (CategoryName.find("TRAP") != std::string::npos) {
		for (int i = 0; i < editOblectTrapList.size(); i++) {
			result.push_back(editOblectTrapList[i]->ObjectName);
			result.push_back(editOblectTrapList[i]->ResourceName);
			result.push_back(editOblectTrapList[i]->GenerateText);
		}
		return result;
	}
	else if (CategoryName.find("BLOCK") != std::string::npos) {
		for (int i = 0; i < editOblectBlockList.size(); i++) {
			result.push_back(editOblectBlockList[i]->ObjectName);
			result.push_back(editOblectBlockList[i]->ResourceName);
			result.push_back(editOblectBlockList[i]->GenerateText);
		}
		return result;
	}

	return result;

}



