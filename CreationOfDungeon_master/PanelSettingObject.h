#pragma once
#include "PanelBase.h"
class PanelSettingObject :
    public PanelBase
{
public:
    PanelSettingObject();
    ~PanelSettingObject();

    void SettingObj(PanelContent pc);

private:
    PanelContent panel;
};

