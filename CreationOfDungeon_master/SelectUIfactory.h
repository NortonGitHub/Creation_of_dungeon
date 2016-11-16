#pragma once
#include "UIFactory.h"
class SelectUIFactory :
	public UIFactory
{
public:
	UIProduct* CreateInstance();

	SelectUIFactory();
	~SelectUIFactory();

};

