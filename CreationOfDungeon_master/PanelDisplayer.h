#pragma once
#include "PanelBase.h"
class PanelDisplayer :
    public PanelBase
{
    //�P���ɒl��s�x�󂯎��\�����邾��
public:
    PanelDisplayer();
    ~PanelDisplayer();

    void Init(PanelContent _panelContent);

    bool IsClicked();

    void DrawDebugPrint() override;

private:
    PanelContent panel;
};

