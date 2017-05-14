#pragma once
#include "PanelBase.h"
class PanelSceneTransition :
    public PanelBase
{
public:
    PanelSceneTransition();
    ~PanelSceneTransition();

    void Init(PanelContent _panelContent);

    bool IsClicked();

    void DrawDebugPrint() override;

private:
    PanelContent panel;
};

