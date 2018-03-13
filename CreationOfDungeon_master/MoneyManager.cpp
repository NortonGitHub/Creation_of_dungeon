#include "MoneyManager.h"
#include "cd_666s\Utility\CSVReader.h"
#include "cd_666s\Resources\AllResourceManager.h"



int MoneyManager::getMoney() {

    return money;

}

void MoneyManager::InitMoney() {

	CSVReader reader;

	std::string fileName = "csv/ShopItem/InitMoney.csv";

	std::vector<std::string> Array;

	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, Array, 1);

	money = std::stoi(Array[0]);

}


void MoneyManager::decreaseMoney(int num) {

    money -= num;

}



void MoneyManager::increaseMoney(int num) {

    money += num;

	if (money >= 999999999) {
		money = 999999999;
	}

}

void MoneyManager::resetMoney() {
	money = 0;
}













