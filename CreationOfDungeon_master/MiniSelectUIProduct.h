#pragma once
#include "UIProduct.h"
class MiniSelectUIProduct :
	public UIProduct
{
public:
	MiniSelectUIProduct();
	~MiniSelectUIProduct();


	void Update(UIContent ui);
	void Draw(UIContent ui);
};

