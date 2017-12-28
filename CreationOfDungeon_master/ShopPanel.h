#pragma once
#include "cd_666s\Render\Sprite.h"

class ShopPanel
{
public:

	enum PanelCategory {
		MONSTER = 0,
		TRAP = 1,
		BLOCK = 2
	};

    ShopPanel();
    ShopPanel(std::string filePath,std::string ObjectName, Vector2D pos, int price, std::string shopPanelCategoryName);
    ~ShopPanel();


	std::string GetShopPanelName();
	int GetPrice();
	Vector2D GetPotision();
	PanelCategory GetShopPanelCategoryName();
	bool GetCanBuy();
	std::string GetShopPanelImagePath();

	bool ClickCheck();

	void Update();
	void Draw();

	void ResetCanBuy();


private:
    
    Sprite shopPanelImage;

	std::string shopPanelImagePath;

    std::string shopPanelName;

	int price;

	PanelCategory shopPanelCategoryName;

	bool canBuy;	//購入可能か（まだ持っていないか、お金が足りないとかは含まない）

};



