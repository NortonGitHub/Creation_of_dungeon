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
#if 0
    if (data_name == "hello") {
        //ñ‚ëËî≠ê∂
    }
    else if (data_name == "start") {
        return std::bind(&ButtonUIProduct::MoveSceneFunction,this);
    }
    else if (data_name == "quit") {
        return std::bind(&ButtonUIProduct::QuitFunction,this);
    }
    /*à»å„ÅAäiî[ÇµÇΩÇ¢ä÷êîÇÇ±Ç±Ç…óÒãìÇ∑ÇÈ*/
    return std::function<void()>();
#endif
    return nullptr;
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
