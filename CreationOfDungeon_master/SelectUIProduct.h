#pragma once
#include "UIProduct.h"
class SelectUIProduct :
	public UIProduct
{
public:
	SelectUIProduct();
	~SelectUIProduct();


	void Update(UIContent ui);
	void Draw(UIContent ui);
};

