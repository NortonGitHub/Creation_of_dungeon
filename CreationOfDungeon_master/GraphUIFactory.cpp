#include "GraphUIFactory.h"
#include "GraphUIProduct.h"


GraphUIFactory::GraphUIFactory()
{
}


GraphUIFactory::~GraphUIFactory()
{
}

UIProduct * GraphUIFactory::CreateInstance(UIContent ui_contents)
{
    return new GraphUIProduct(ui_contents);
}

