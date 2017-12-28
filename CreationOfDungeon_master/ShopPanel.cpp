#include "ShopPanel.h"
#include "cd_666s\Resources\AllResourceManager.h"
#include "cd_666s/DebugDraw.h"
#include "cd_666s/InputManager/MouseInput.h"
#include "ShopAssortment.h"

ShopPanel::ShopPanel()
{
    
}

ShopPanel::ShopPanel(std::string filePath, std::string ObjectName, Vector2D pos, int price, std::string shopPanelCategoryName) {
    //画像が読み込めていない
    //シーンが破棄される前にレンダーに登録されているため、シーンの破棄と同時に破棄されているっぽい
    this->shopPanelImage.Load("resource/graph/" + filePath + ".png");

    this->shopPanelName = ObjectName;

    shopPanelImage.SetPosition(pos);

	this->shopPanelImage.SetPriority(Sprite::Priority::UI);
	this->shopPanelImage.SetScale(Vector2D(128.0 / shopPanelImage.GetSize()._x, 128.0 / shopPanelImage.GetSize()._y));


	this->price = price;

	if (shopPanelCategoryName == "MONSTER") {
		this->shopPanelCategoryName = PanelCategory::MONSTER;
	}else if (shopPanelCategoryName == "TRAP") {
		this->shopPanelCategoryName = PanelCategory::TRAP;
	}else if (shopPanelCategoryName == "BLOCK") {
		this->shopPanelCategoryName = PanelCategory::BLOCK;
	}

	canBuy = ShopAssortment::getInstance()->getCanBuy(shopPanelName, this->shopPanelCategoryName);
	

}

ShopPanel::~ShopPanel()
{
}


std::string ShopPanel::GetShopPanelName() {
	return shopPanelName;
}


int ShopPanel::GetPrice() {
	return price;
}

ShopPanel::PanelCategory ShopPanel::GetShopPanelCategoryName() {
	return shopPanelCategoryName;
}

void ShopPanel::ResetCanBuy() {
	canBuy = ShopAssortment::getInstance()->getCanBuy(shopPanelName, this->shopPanelCategoryName);
}

void ShopPanel::Update() {



}


void ShopPanel::Draw() {

	int digit = 6 - std::to_string(price).length();
	std::string digit_s = "";

	for (int i = 0; i < digit; i++) {
		digit_s += " ";
	}

	Debug::DrawString(shopPanelImage.GetPosition() + Vector2D(0, shopPanelImage.GetTexturePtr().lock()->GetBaseSize()._y + 15), digit_s + std::to_string(price) + "M", Color4(0, 0, 0, 1), 32);

	if (!canBuy) {
		Debug::DrawString(shopPanelImage.GetPosition() + Vector2D(0, shopPanelImage.GetTexturePtr().lock()->GetBaseSize()._y / 2 - 16), "売り切れ", Color4(1, 0, 0, 1), 32);
	}

}


Vector2D ShopPanel::GetPotision() {
	return shopPanelImage.GetPosition();
}

bool ShopPanel::GetCanBuy() {
	return canBuy;
}


bool ShopPanel::ClickCheck() {

	if (!MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
		return false;

	//クリック位置を取得
	auto cursorPos = MOUSE->GetCursorPos();

	auto texturePtr = shopPanelImage.GetTexturePtr();
	if (texturePtr.expired())
		return false;

	auto texture = texturePtr.lock();
	auto size = texture->GetBaseSize();
	if (cursorPos._x < shopPanelImage.GetPosition()._x)
		return false;
	if (cursorPos._y < shopPanelImage.GetPosition()._y)
		return false;
	if (shopPanelImage.GetPosition()._x + size._x < cursorPos._x)
		return false;
	if (shopPanelImage.GetPosition()._y + size._y < cursorPos._y)
		return false;

	return true;

}

