#include "MessageUIFactory.h"
#include "MessageUIProduct.h"

MessageUIFactory::MessageUIFactory()
{
}


MessageUIFactory::~MessageUIFactory()
{
}

UIProduct * MessageUIFactory::CreateInstance()
{
	return new MessageUIProduct();
}
