#pragma once
#include "PanelContent.h"
#include "cd_666s/InputManager/InputManager.h"

#include "cd_666s/Resources/ResourceManager.h"
#include "cd_666s/TilebaseAI/Character.h"
#include "Graph.h"

class PanelBase : public GraphicalObject
{
public:
    PanelBase();
    ~PanelBase();

    virtual void Update();
    virtual void Draw();

    virtual void Init(PanelContent& _panelContent);

    virtual std::string GetCategoryName();
    virtual std::string GetTypeName();

    virtual void SetSettingObject(std::vector<PanelBase>& _tps);

    virtual bool IsClicked();

    virtual bool IsEnable();    //

    virtual void DrawDebugPrint();

    bool GetIsClicked(PanelContent& panel);

    //std::shared_ptr<PanelContent> _pobj;
    // virtual void SetPanel

    std::string GetPanelClassName() const { return _class_name; };

protected:
    //    PanelContent panel;
    std::string _class_name;
};