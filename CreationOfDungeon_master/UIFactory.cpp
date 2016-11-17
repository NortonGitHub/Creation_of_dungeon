#include "UIFactory.h"



UIFactory::UIFactory()
{
}


UIFactory::~UIFactory()
{
}

UIProduct * UIFactory::GetInstance()
{
    UIProduct* uip = CreateInstance();

    return uip;
}

UIFactory::UIFactory(std::string file_name)
{

}
