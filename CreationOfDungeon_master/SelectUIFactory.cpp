#include "SelectUIFactory.h"
#include "SelectUIProduct.h"


SelectUIFactory::SelectUIFactory()
{
}


SelectUIFactory::~SelectUIFactory()
{
}

UIProduct * SelectUIFactory::CreateInstance()
{
	return new SelectUIProduct();
}
