#include "UIProduct.h"


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
        //問題発生
    }
    else if (data_name == "start") {
        return std::bind(&ButtonUIProduct::MoveSceneFunction,this);
    }
    else if (data_name == "quit") {
        return std::bind(&ButtonUIProduct::QuitFunction,this);
    }
    /*以後、格納したい関数をここに列挙する*/
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
