#pragma once
#include "SceneBase.h"

#include "PanelBase.h"
#include "PanelContent.h"
#include "PanelSettingObject.h"
#include "EditObject.h"
#include "ObjectTextPanel.h"

class WorldMap_Menu
{
public:
	WorldMap_Menu();
	~WorldMap_Menu();

	void Update();
	void Draw();

	void Init();

	void SetActive(bool flag);
	bool GetIsActive();


private:
	const size_t NPOS;

	std::string class_name;

	std::vector<std::string> _functions;

	std::shared_ptr<ObjectTextPanel> objectTextPanel;

	//std::vector<std::shared_ptr<PanelBase>> panels;  //UI

	void PanelFunction();
	void PanelAffectObjectsFunction(std::shared_ptr<PanelBase> panel);
	void PanelDisplayerFunction(std::shared_ptr<PanelBase> panel);
	void PanelSettingObjectFunction(std::shared_ptr<PanelBase> panel);

	void PanelPageChangeObjectFunction(std::shared_ptr<PanelBase> panel);

	void SetPanelInstance(std::string key_name, ::shared_ptr<PanelBase>& panel, PanelContent& temp);

	void DebugOutputFile();

	std::shared_ptr<PanelSettingObject> selectedObject;


	std::string selectPanelCategory;

	Sound _cancelSE;

	Sprite _selectCategoryGr;
	Sprite _selectObjectGr;

	EditObject editObject;

	//ÉyÅ[ÉWä÷åW
	int pageNum;
	int pageMaxNum;

	bool isActive;

};

