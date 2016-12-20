#include "MessageUIFactory.h"
#include "MessageUIProduct.h"

MessageUIFactory::MessageUIFactory()
{
}


MessageUIFactory::~MessageUIFactory()
{
}

UIProduct * MessageUIFactory::CreateInstance(UIContent ui_contents)
{
    return new MessageUIProduct(ui_contents);
}
