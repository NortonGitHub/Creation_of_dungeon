#include "UIProduct.h"

#include "ButtonUIProduct.h"

UIProduct::UIProduct()
{
}


UIProduct::~UIProduct()
{
}

std::function<void()> UIProduct::GetUI(std::string data_name)
{

    if (data_name == "hello") {
        return std::bind(&ButtonUIProduct::A);
    }
    else if (data_name == "start") {

    }
    /*à»å„ÅAäiî[ÇµÇΩÇ¢ä÷êîÇÇ±Ç±Ç…óÒãìÇ∑ÇÈ*/
    return std::function<void()>();
}

#if 0
void UIProduct::Update(std::vector<UIContent>& using_UI)
{
    for (auto ui : using_UI) {

        Update();
    }
}
#endif

#if 0
void UIProduct::Draw(std::vector<UIContent>& using_UI)
{
    for (auto ui : using_UI) {
        Draw(ui);
    }
}
#endif
