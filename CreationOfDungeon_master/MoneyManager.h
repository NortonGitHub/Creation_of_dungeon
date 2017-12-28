#pragma once



class MoneyManager {

private:
    MoneyManager() {
        money = 0;
    };
    ~MoneyManager() = default;

    int money;


public:
    MoneyManager(const MoneyManager&) = delete;
    MoneyManager& operator=(const MoneyManager&) = delete;
    MoneyManager(MoneyManager&&) = delete;
    MoneyManager& operator=(MoneyManager&&) = delete;

    static MoneyManager* getInstance() {
        static MoneyManager inst;
        return &inst;
    }

    int getMoney();
	void resetMoney();

    void decreaseMoney(int num);

    void increaseMoney(int num);


};









