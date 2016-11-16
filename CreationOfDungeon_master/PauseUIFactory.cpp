#include "PauseUIFactory.h"
#include "PauseUIProduct.h"


PauseUIFactory::PauseUIFactory()
{
}


PauseUIFactory::~PauseUIFactory()
{
}

UIProduct * PauseUIFactory::CreateInstance()
{
	return new PauseUIProduct();
}
