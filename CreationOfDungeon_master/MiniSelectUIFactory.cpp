#include "MiniSelectUIFactory.h"
#include "MiniSelectUIProduct.h"


MiniSelectUIFactory::MiniSelectUIFactory()
{
}


MiniSelectUIFactory::~MiniSelectUIFactory()
{
}

UIProduct * MiniSelectUIFactory::CreateInstance()
{
    return new MiniSelectUIProduct();
}
