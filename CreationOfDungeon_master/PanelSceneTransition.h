#pragma once
#include "PanelBase.h"
class PanelSceneTransition :
    public PanelBase
{
public:
    PanelSceneTransition();
    PanelSceneTransition(PanelContent _panelContent);
    
    ~PanelSceneTransition();

    void Update() override;
    void Draw() override;

    void Init(PanelContent& _panelContent);

    bool IsClicked();

    void DrawDebugPrint() override;

private:
    PanelContent panel;
};

