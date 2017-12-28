#include <string>
#include "cd_666s\Render\Sprite.h"
#include <vector>
#include "ShopPanel.h"
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
	bool canBuy;	//w“ü‰Â”\‚©i‚¨‹à‚ª‘«‚è‚Ä‚¢‚é‚©‚àŠÜ‚Şj

public:

	ObjectTextPanel();
	ObjectTextPanel(std::string className);

	~ObjectTextPanel();

	void Init();

	void Update();
	void Draw();

	void ReadMessageText();
	void SetMessage(std::shared_ptr<ShopPanel> selectShopPanel);

	bool BuyCheck();

};

