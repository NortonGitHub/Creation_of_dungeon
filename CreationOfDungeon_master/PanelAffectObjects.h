#pragma once
#include "PanelBase.h"

class PanelAffectObjects :
    public PanelBase
{
    //�J�e�S���I��
public:
    PanelAffectObjects();
    ~PanelAffectObjects();

    void Update();
    void Draw();

    void Init(PanelContent _panelContent);

    std::string GetCategoryName();

    void SetSettingObject(std::vector<PanelBase>& _tps);

    void DrawDebugPrint() override;

    bool IsClicked();

private:
    PanelContent panel;
};

