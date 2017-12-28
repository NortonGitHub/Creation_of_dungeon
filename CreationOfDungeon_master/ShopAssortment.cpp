#include "ShopAssortment.h"
#include "cd_666s\Utility\CSVReader.h"
#include "cd_666s\Resources\AllResourceManager.h"
#include <fstream>
#include <string>
#include <sstream>
#include "DxLib.h"
#include "MoneyManager.h"


void ShopAssortment::setShopItemList() {

	CSVReader reader;

	std::string fileName = "csv/Edit/BLOCK.csv";

	std::vector<std::string> ShopItemArray;

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, ShopItemArray, 1);

	for (int j = 0; j < ShopItemArray.size(); j += 3) {
		std::shared_ptr<ShopItem_Block> shopItem = make_shared<ShopItem_Block>();

		shopItem->ObjectName = ShopItemArray[j];
		shopItem->isHaveing = false;

		shopItemBlockList.push_back(shopItem);
	}

	fileName = "csv/Edit/TRAP.csv";

	ShopItemArray.clear();

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, ShopItemArray, 1);

	for (int j = 0; j < ShopItemArray.size(); j += 3) {
		std::shared_ptr<ShopItem_Trap> shopItem = make_shared<ShopItem_Trap>();

		shopItem->ObjectName = ShopItemArray[j];
		shopItem->isHaveing = false;
		shopItem->level = -1;

		shopItemTrapList.push_back(shopItem);
	}

	fileName = "csv/Edit/MONSTER.csv";

	ShopItemArray.clear();

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, ShopItemArray, 1);

	for (int j = 0; j < ShopItemArray.size(); j += 3) {
		std::shared_ptr<ShopItem_Monster> shopItem = make_shared<ShopItem_Monster>();

		shopItem->ObjectName = ShopItemArray[j];
		shopItem->isHaveing = false;
		shopItem->level = -1;

		shopItemMonsterList.push_back(shopItem);
	}

	fileName = "csv/Edit/InitHave.csv";

	ShopItemArray.clear();

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, ShopItemArray, 1);

	for (int i = 0; i < ShopItemArray.size(); i += 2) {
		if (ShopItemArray[i + 1] == "BLOCK") {
			for (int j = 0; j < shopItemBlockList.size(); j++) {
				if (shopItemBlockList[j]->ObjectName == ShopItemArray[i]) {
					shopItemBlockList[j]->isHaveing = true;
				}
			}
		}
		else if (ShopItemArray[i + 1] == "TRAP") {
			for (int j = 0; j < shopItemTrapList.size(); j++) {
				if (shopItemTrapList[j]->ObjectName == ShopItemArray[i]) {
					shopItemTrapList[j]->isHaveing = true;
					shopItemTrapList[j]->level = 1;
				}
			}
		}
		else if (ShopItemArray[i + 1] == "MONSTER") {
			for (int j = 0; j < shopItemMonsterList.size(); j++) {
				if (shopItemMonsterList[j]->ObjectName == ShopItemArray[i]) {
					shopItemMonsterList[j]->isHaveing = true;
					shopItemMonsterList[j]->level = 1;
				}
			}
		}
	}

}



void ShopAssortment::BuyItem(std::shared_ptr<ShopPanel> shopPanel) { //ˆø”‚ÍshopItemList‚Ì“Y‚¦Žš‚Ì”Ô† –ß‚è’l‚Íw“ü¬Œ÷‚Å1AŽ¸”s‚Å0

	MoneyManager::getInstance()->decreaseMoney(shopPanel->GetPrice());

	ShopPanel::PanelCategory pc = shopPanel->GetShopPanelCategoryName();
	std::string objectName = shopPanel->GetShopPanelName();

	if (pc == ShopPanel::PanelCategory::BLOCK) {
		for (int i = 0; i < shopItemBlockList.size(); i++) {
			if (shopItemBlockList[i]->ObjectName == objectName) {
				shopItemBlockList[i]->isHaveing = true;
			}
		}
	}
	else if (pc == ShopPanel::PanelCategory::TRAP) {
		for (int i = 0; i < shopItemTrapList.size(); i++) {
			if (shopItemTrapList[i]->ObjectName == objectName) {
				shopItemTrapList[i]->isHaveing = true;
			}
		}
	}
	else if (pc == ShopPanel::PanelCategory::MONSTER) {
		for (int i = 0; i < shopItemMonsterList.size(); i++) {
			if (shopItemMonsterList[i]->ObjectName == objectName) {
				shopItemMonsterList[i]->isHaveing = true;
			}
		}
	}

}


bool ShopAssortment::getCanBuy(std::string objectName, ShopPanel::PanelCategory pc) {

	if (pc == ShopPanel::PanelCategory::BLOCK) {
		for (int i = 0; i < shopItemBlockList.size(); i++) {
			if (shopItemBlockList[i]->ObjectName == objectName) {
				return !shopItemBlockList[i]->isHaveing;
			}
		}
	}
	else if (pc == ShopPanel::PanelCategory::TRAP) {
		for (int i = 0; i < shopItemTrapList.size(); i++) {
			if (shopItemTrapList[i]->ObjectName == objectName) {
				return !shopItemTrapList[i]->isHaveing;
			}
		}
	}
	else if (pc == ShopPanel::PanelCategory::MONSTER) {
		for (int i = 0; i < shopItemMonsterList.size(); i++) {
			if (shopItemMonsterList[i]->ObjectName == objectName) {
				return !shopItemMonsterList[i]->isHaveing;
			}
		}
	}

	return false;

}


bool ShopAssortment::getCanSetObject(std::string objectName, ShopPanel::PanelCategory pc) {

	if (pc == ShopPanel::PanelCategory::BLOCK) {
		for (int i = 0; i < shopItemBlockList.size(); i++) {
			if (shopItemBlockList[i]->ObjectName == objectName) {
				return shopItemBlockList[i]->isHaveing;
			}
		}
	}
	else if (pc == ShopPanel::PanelCategory::TRAP) {
		for (int i = 0; i < shopItemTrapList.size(); i++) {
			if (shopItemTrapList[i]->ObjectName == objectName) {
				return shopItemTrapList[i]->isHaveing;
			}
		}
	}
	else if (pc == ShopPanel::PanelCategory::MONSTER) {
		for (int i = 0; i < shopItemMonsterList.size(); i++) {
			if (shopItemMonsterList[i]->ObjectName == objectName) {
				return shopItemMonsterList[i]->isHaveing;
			}
		}
	}

	return false;

}




