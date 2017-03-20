#pragma once
#include "PanelContent.h"
class PanelBase
{
public:
    PanelBase();
    ~PanelBase();

    virtual void Update();
    virtual void Draw();

    virtual std::string GetCategoryName();
    virtual void SetObject(PanelBase _other_panel);

   // virtual void SetPanel
};

