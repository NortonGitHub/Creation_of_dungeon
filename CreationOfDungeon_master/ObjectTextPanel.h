#include <string>
#include "cd_666s\Render\Sprite.h"
#include <vector>
#include "ShopPanel.h"
#include "PanelSettingObject.h"
#pragma once

class ObjectTextPanel
{

private:

	enum PanelType {
		Shop = 0,
		Edit = 1
	};

	PanelType panelType;

	Sprite _messageWindow;
	Sprite _ObjectImage;

	struct MessageText {

		std::string ObjectName;
		std::string ResourceName;
		std::string DisplayName;
		std::string ItemText;
	};

	std::vector<std::vector<std::shared_ptr<MessageText>>> messageText;

	ShopPanel::PanelCategory messageTextCategory;
	int messageTextArrayNum;

	Sprite _buyButton;

	bool existBuy;	//購入ボタンは存在するか
	bool canBuy;	//購入可能か（お金が足りているかも含む）

	bool existLevelUp;	//レベルアップ先は存在するか
	bool canLevelUp;	//レベルアップ可能か（お金が足りているかも含む）

	int Level;
	int LevelUpCost;


	Sound _cancelSE;
	

public:

	ObjectTextPanel();
	ObjectTextPanel(std::string className);

	~ObjectTextPanel();

	void Init();
	void Init_Shop();
	void Init_Edit();

	void Update();
	void Draw();

	void ReadMessageText();
	void SetMessage(std::shared_ptr<ShopPanel> selectShopPanel);
	void SetMessage(std::shared_ptr<PanelSettingObject> selectPanel);
	
	void ResetMessage();

	bool BuyCheck();

	bool EvolCheck();

};

