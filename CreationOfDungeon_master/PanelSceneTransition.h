#pragma once
#include "PanelBase.h"
class PanelSceneTransition :
    public PanelBase
{
public:
    PanelSceneTransition();
    PanelSceneTransition(PanelContent& _panelContent);
    ~PanelSceneTransition();

    void Update() override;
    void Draw() override;

    void Init(PanelContent& _panelContent) override;

    std::string GetCategoryName() override;
    std::string GetTypeName() override;

    bool IsClicked() override;

    void DrawDebugPrint() override;

private:
    PanelContent panel;
};
