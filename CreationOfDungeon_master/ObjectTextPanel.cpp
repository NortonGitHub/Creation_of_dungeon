#include "ObjectTextPanel.h"
#include "cd_666s\Utility\CSVReader.h"
#include "cd_666s\Resources\AllResourceManager.h"
#include "cd_666s/DebugDraw.h"
#include <regex>
#include "cd_666s/InputManager/MouseInput.h"
#include "MoneyManager.h"

ObjectTextPanel::ObjectTextPanel()
{



}


ObjectTextPanel::ObjectTextPanel(std::string className) {

	if (className == "shop") {

		panelType = ObjectTextPanel::PanelType::Shop;

	}
	else {

		panelType = ObjectTextPanel::PanelType::Edit;

	}

	Init();


}

ObjectTextPanel::~ObjectTextPanel()
{



}


void ObjectTextPanel::Init() {

	_messageWindow.Load("resource/graph/ui/message_window.png");
	_messageWindow.SetPosition(Vector2D(150, 540));
	_messageWindow.SetPriority(Sprite::Priority::UI);

	_buyButton.Load("resource/graph/shop/buyButton.png");
	_buyButton.SetPosition(Vector2D(775, 650));
	_buyButton.SetPriority(static_cast<int>(Sprite::Priority::UI) + 1);
	_buyButton.SetDisplayMode(false);

	ReadMessageText();

	messageTextCategory = ShopPanel::PanelCategory::MONSTER;

	messageTextArrayNum = -1;

	canBuy = false;

}

void ObjectTextPanel::Update() {

}

void ObjectTextPanel::Draw() {

	if (messageTextArrayNum >= 0) {

		std::regex regex("\\\\n");
		std::string itemText = std::regex_replace(messageText[messageTextCategory][messageTextArrayNum]->ItemText, regex, "\n");

		std::string displayName = messageText[messageTextCategory][messageTextArrayNum]->DisplayName;

		int textNum = 0;
		int smalltextNum = 0;
		std::string temp = displayName;
		while (!temp.empty()) {
			if (IsDBCSLeadByte(temp[0]) == 0)
			{
				temp.erase(0, 1);
				smalltextNum++;
			}
			else
			{
				temp.erase(0, 2);
				textNum++;
			}
		}

		Debug::DrawString(Vector2D(320, 560), displayName, Color4(0, 0, 0, 1), 24);
		Debug::DrawLine(Vector2D(320, 585), Vector2D(320 + textNum * 25 + smalltextNum * 13, 585), Color4(0, 0, 0, 1));
		Debug::DrawString(Vector2D(340, 600), itemText, Color4(0, 0, 0, 1), 18);
	}

}



void ObjectTextPanel::ReadMessageText() {

	CSVReader reader;

	std::string fileName = "csv/text/block.csv";
	std::vector<std::string> messageArray;
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, messageArray, 1);

	messageText.clear();
	messageText.resize(3);

	std::vector<std::shared_ptr<MessageText>> tempMessage;
	tempMessage.clear();
	if (!messageArray.empty() && !messageArray.front().empty()) {
		for (int i = 0; i < messageArray.size(); i += 4) {

			std::shared_ptr<MessageText> mt = std::make_shared<MessageText>();

			mt->ObjectName = messageArray[i];
			mt->ResourceName = messageArray[i + 1];
			mt->DisplayName = messageArray[i + 2];
			mt->ItemText = messageArray[i + 3];

			tempMessage.push_back(mt);

		}
	}

	messageText[ShopPanel::PanelCategory::BLOCK] = tempMessage;


	tempMessage.clear();
	messageArray.clear();
	fileName = "csv/text/monster.csv";
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, messageArray, 1);
	if (!messageArray.empty() && !messageArray.front().empty()) {
		for (int i = 0; i < messageArray.size(); i += 4) {

			std::shared_ptr<MessageText> mt = std::make_shared<MessageText>();

			mt->ObjectName = messageArray[i];
			mt->ResourceName = messageArray[i + 1];
			mt->DisplayName = messageArray[i + 2];
			mt->ItemText = messageArray[i + 3];

			tempMessage.push_back(mt);

		}
	}

	messageText[ShopPanel::PanelCategory::MONSTER] = tempMessage;


	tempMessage.clear();
	messageArray.clear();
	fileName = "csv/text/trap.csv";
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, messageArray, 1);
	if (!messageArray.empty() && !messageArray.front().empty()) {
		for (int i = 0; i < messageArray.size(); i += 4) {

			std::shared_ptr<MessageText> mt = std::make_shared<MessageText>();

			mt->ObjectName = messageArray[i];
			mt->ResourceName = messageArray[i + 1];
			mt->DisplayName = messageArray[i + 2];
			mt->ItemText = messageArray[i + 3];

			tempMessage.push_back(mt);

		}
	}

	messageText[ShopPanel::PanelCategory::TRAP] = tempMessage;


}

void ObjectTextPanel::SetMessage(std::shared_ptr<ShopPanel> selectShopPanel) {

	messageTextCategory = selectShopPanel->GetShopPanelCategoryName();
	canBuy = selectShopPanel->GetCanBuy();

	if (canBuy && MoneyManager::getInstance()->getMoney() >= selectShopPanel->GetPrice()) {
		_buyButton.SetDisplayMode(true);
	}
	else {
		canBuy = false;
		_buyButton.SetDisplayMode(false);
	}

	for (int i = 0; i < messageText[messageTextCategory].size(); i++) {
		if (messageText[messageTextCategory][i]->ObjectName == selectShopPanel->GetShopPanelName()) {
			messageTextArrayNum = i;
			return;
		}
		messageTextArrayNum = -1;
	}
	messageTextArrayNum = -1;

}



bool ObjectTextPanel::BuyCheck() {

	if (!canBuy)
		return false;

	if (!MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
		return false;

	Vector2D pos = _buyButton.GetPosition();
	Vector2D size = _buyButton.GetTexturePtr().lock()->GetBaseSize();

	//クリック位置を取得
	auto cursorPos = MOUSE->GetCursorPos();

	if (cursorPos._x < pos._x)
		return false;
	if (cursorPos._y < pos._y)
		return false;
	if (pos._x + size._x < cursorPos._x)
		return false;
	if (pos._y + size._y < cursorPos._y)
		return false;

	return true;

}

