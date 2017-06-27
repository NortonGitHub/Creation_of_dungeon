#pragma once
#include "PanelBase.h"
class PanelSettingObject :
    public PanelBase
{
public:
    PanelSettingObject();
    PanelSettingObject(PanelContent& _panelContent);
    ~PanelSettingObject();

    void Update() override;
    void Draw() override;

    void Init(PanelContent& _panelContent) override;

    std::string GetTypeName() override;

    bool IsClicked() override;

    bool IsEnable() override;

    void DrawDebugPrint() override;

private:
    PanelContent panel;

    bool _isEnable;
};

