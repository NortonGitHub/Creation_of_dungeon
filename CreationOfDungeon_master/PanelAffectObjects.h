#pragma once
#include "PanelBase.h"
class PanelAffectObjects :
    public PanelBase
{
    //ƒJƒeƒSƒŠ‘I‘ð
public:
    PanelAffectObjects();
    ~PanelAffectObjects();

    void Update();
    void Draw();

    std::string GetCategoryName();

    void SetObject(PanelBase _other_panel);

private:
    PanelContent panel;
};

