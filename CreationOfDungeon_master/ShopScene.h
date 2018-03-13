#pragma once
#include "SceneBase.h"
#include "ShopPanel.h"
#include "ObjectTextPanel.h"

class ShopScene :
    public SceneBase
{

private:

    std::string class_name;

    std::string shopNum;

    std::vector<std::shared_ptr<ShopPanel>> shopPanelList;
	std::shared_ptr<ShopPanel> selectShopPanel;

	Sprite _background;
	Sprite _exitButton;
	Sprite _moneyBox;
	Sprite _shopTable_Up;
	Sprite _shopTable_Down;

	

	Sprite _selectFrame;

	std::shared_ptr<ObjectTextPanel> objectTextPanel;

public:

    ShopScene();
    ShopScene(std::string shopNum);
    ~ShopScene();

    std::string GetClassNameData() const {
        return class_name;
    }


	void Init();

    SceneBase* Update();
    SceneBase* Update(UIManager _ui) override;
    void Draw();

	bool ClickCheck(Vector2D pos, Vector2D size);

	void setSelectShopPanel(std::shared_ptr<ShopPanel> selectShopPanel);


};
