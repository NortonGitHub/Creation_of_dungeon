#pragma once
#include "PanelBase.h"

class PanelAffectObjects :
    public PanelBase
{
    //�J�e�S���I��
public:
    PanelAffectObjects();
    PanelAffectObjects(PanelContent& _panelContent);
    ~PanelAffectObjects();

    void Update() override;
    void Draw() override;

    void Init(PanelContent& _panelContent) override;

    std::string GetCategoryName() override;
    std::string GetTypeName() override;

    void SetSettingObject(std::vector<PanelBase>& _tps) override;

    void DrawDebugPrint() override;

    bool IsClicked() override;

private:
    PanelContent panel;
};

