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

    std::string GetCategoryName();

    void SetObject(PanelBase _other_panel);

private:
    PanelContent panel;
};

