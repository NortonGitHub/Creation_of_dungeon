#pragma once
#include "PanelBase.h"
class PanelDisplayer :
    public PanelBase
{
    //単純に値を都度受け取り表示するだけ
public:
    PanelDisplayer();
    PanelDisplayer(PanelContent _panelContent);
    ~PanelDisplayer();

    void Update() override;
    void Draw() override;

    void Init(PanelContent _panelContent);

    bool IsClicked();

    void DrawDebugPrint() override;

private:
    PanelContent panel;
};

