#include "ButtonUIFactory.h"
#include "ButtonUIProduct.h"


ButtonUIFactory::ButtonUIFactory()
{
}


ButtonUIFactory::~ButtonUIFactory()
{
}

UIProduct * ButtonUIFactory::CreateInstance(UIContent ui_contents)
{
    return new ButtonUIProduct(ui_contents);
}
