#pragma once
#include "PanelBase.h"
class PanelPageChangeObject :
	public PanelBase
{
public:
	PanelPageChangeObject();
	PanelPageChangeObject(PanelContent _panelContent);
	~PanelPageChangeObject();

	void Update() override;
	void Draw() override;

	void Init(PanelContent _panelContent);

	void SetSettingObject(std::vector<std::shared_ptr<PanelBase>> _tps, EditObject editObject, std::string CategoryName, int pageNum);

	void DrawDebugPrint() override;

	bool IsClicked();

	bool IsPageUP();	//ページが進むボタンかどうか

private:
	PanelContent panel;

};

