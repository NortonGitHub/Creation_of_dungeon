#include "UIProduct.h"



UIProduct::UIProduct()
{
}


UIProduct::~UIProduct()
{
}

void UIProduct::Update(std::vector<UIContent>& using_UI)
{
	for (auto ui : using_UI) {

		Update(ui);
	}
}

void UIProduct::Draw(std::vector<UIContent>& using_UI)
{
	for (auto ui : using_UI) {
		Draw(ui);
	}
}
