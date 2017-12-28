#include "MoneyManager.h"




int MoneyManager::getMoney() {

    return money;

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













