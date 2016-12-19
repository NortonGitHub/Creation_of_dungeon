#include "ButtonUIFactory.h"
#include "ButtonUIProduct.h"


ButtonUIFactory::ButtonUIFactory()
{
}


ButtonUIFactory::~ButtonUIFactory()
{
}

UIProduct * ButtonUIFactory::CreateInstance()
{
    return new ButtonUIProduct();
}
