#include "PanelSceneTransition.h"



PanelSceneTransition::PanelSceneTransition()
{
}


PanelSceneTransition::~PanelSceneTransition()
{
}

void PanelSceneTransition::Init(PanelContent _panelContent)
{
    panel = _panelContent;
}

bool PanelSceneTransition::IsClicked()
{
    return GetIsClicked(panel);
}
