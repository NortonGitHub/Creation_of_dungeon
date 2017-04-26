#include "PanelDisplayer.h"



PanelDisplayer::PanelDisplayer()
{
}


PanelDisplayer::~PanelDisplayer()
{
}

void PanelDisplayer::Init(PanelContent _panelContent)
{
    panel = _panelContent;
}

bool PanelDisplayer::IsClicked()
{
    return GetIsClicked(panel);
}
