#include <string>
#include <vector>
#include <memory>
#include "ShopPanel.h"
#pragma once


class ShopAssortment {

private:
    ShopAssortment() = default;
    ~ShopAssortment() = default;

	//�g���\���̂��ȉ���
	struct ShopItem_Block {   //�X�̔��蕨�̏��

		std::string ObjectName;   //�I�u�W�F�N�g��
		bool isHaveing;             //�������Ă��邩�ǂ���   true�ŏ������Ă���i�w���ς݁j

	};

	struct ShopItem_Trap {   //�X�̔��蕨�̏��

		std::string ObjectName;   //�I�u�W�F�N�g��
		bool isHaveing;             //�������Ă��邩�ǂ���   true�ŏ������Ă���i�w���ς݁j
		int level;

	};

	struct ShopItem_Monster {   //�X�̔��蕨�̏��

		std::string ObjectName;   //�I�u�W�F�N�g��
		bool isHaveing;             //�������Ă��邩�ǂ���   true�ŏ������Ă���i�w���ς݁j
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

