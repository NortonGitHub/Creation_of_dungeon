#include <string>
#include <vector>
#include <memory>
#include "ShopPanel.h"
#pragma once


class ShopAssortment {

private:
    ShopAssortment() = default;
    ~ShopAssortment() = default;

	//使う構造体を以下に
	struct ShopItem_Block {   //店の売り物の情報

		std::string ObjectName;   //オブジェクト名
		bool isHaveing;             //所持しているかどうか   trueで所持している（購入済み）

	};

	struct ShopItem_Trap {   //店の売り物の情報

		std::string ObjectName;   //オブジェクト名
		bool isHaveing;             //所持しているかどうか   trueで所持している（購入済み）
		int level;

	};

	struct ShopItem_Monster {   //店の売り物の情報

		std::string ObjectName;   //オブジェクト名
		bool isHaveing;             //所持しているかどうか   trueで所持している（購入済み）
		int level;

	};

	std::vector<std::shared_ptr<ShopItem_Block>> shopItemBlockList;
	std::vector<std::shared_ptr<ShopItem_Trap>> shopItemTrapList;
	std::vector<std::shared_ptr<ShopItem_Monster>> shopItemMonsterList;

public:
    ShopAssortment(const ShopAssortment&) = delete;
    ShopAssortment& operator=(const ShopAssortment&) = delete;
    ShopAssortment(ShopAssortment&&) = delete;
    ShopAssortment& operator=(ShopAssortment&&) = delete;

    static ShopAssortment* getInstance() {
        static ShopAssortment inst;
        return &inst;
    }

    void setShopItemList();

	bool getCanBuy(std::string objectName, ShopPanel::PanelCategory pc);
	bool getCanSetObject(std::string objectName, ShopPanel::PanelCategory pc);

    void BuyItem(std::shared_ptr<ShopPanel> shopPanel);

};

