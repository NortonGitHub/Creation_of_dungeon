#pragma once
#include "PanelContent.h"
#include "cd_666s/InputManager/InputManager.h"

class PanelBase
{
public:
    PanelBase();
    ~PanelBase();

    virtual void Update();
    virtual void Draw();

    virtual void Init(PanelContent _panelContent);

    virtual std::string GetCategoryName();

    virtual void SetSettingObject(std::vector<PanelBase>& _tps);

    virtual bool IsClicked();

    bool GetIsClicked(PanelContent panel);

   // virtual void SetPanel
};

