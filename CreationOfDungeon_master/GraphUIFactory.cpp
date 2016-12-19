#include "GraphUIFactory.h"
#include "GraphUIProduct.h"


GraphUIFactory::GraphUIFactory()
{
}


GraphUIFactory::~GraphUIFactory()
{
}

UIProduct * GraphUIFactory::CreateInstance()
{
    return new GraphUIProduct();
}

