#include "UIFactory.h"



UIFactory::UIFactory()
{
}


UIFactory::~UIFactory()
{
}

UIProduct * UIFactory::GetInstance(UIContent ui_contents)
{
    UIProduct* uip = CreateInstance();

    return uip;
}

UIFactory::UIFactory(std::string file_name)
{

}
