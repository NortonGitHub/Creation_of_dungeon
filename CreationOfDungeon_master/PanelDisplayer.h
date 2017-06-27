#pragma once
#include "PanelBase.h"
class PanelDisplayer :
    public PanelBase
{
    //単純に値を都度受け取り表示するだけ
public:
    PanelDisplayer();
    PanelDisplayer(PanelContent& _panelContent);
    ~PanelDisplayer();

    void Update() override;
    void Draw() override;

    void Init(PanelContent& _panelContent) override;

    void SetSettingObject(std::vector<PanelBase>& _tps) override;

    bool IsClicked() override;

    std::string GetTypeName() override;

    void DrawDebugPrint() override;

private:
    PanelContent panel;
};

