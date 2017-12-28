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
	bool canBuy;	//çwì¸â¬î\Ç©ÅiÇ®ã‡Ç™ë´ÇËÇƒÇ¢ÇÈÇ©Ç‡ä‹ÇﬁÅj
	bool canLevelUp;

	int Level;
	int LevelUpCost;

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

