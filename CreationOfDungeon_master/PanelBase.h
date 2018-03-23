#pragma once
#include "PanelContent.h"
#include "cd_666s/InputManager/InputManager.h"

#include "cd_666s/Resources/ResourceManager.h"
#include "cd_666s/TilebaseAI/Character.h"
#include "Graph.h"

#include "cd_666s\TilebaseAI\GraphicalObject.h"
#include "EditObject.h"

class PanelBase : public GraphicalObject
{
public:
    PanelBase();
    ~PanelBase();

    virtual void Update();
    virtual void Draw();

    virtual void Init(PanelContent& _panelContent);

    virtual std::string GetCategoryName();

    virtual void SetSettingObject(std::vector<PanelBase>& _tps);
    virtual void SetSettingObject(std::vector<std::shared_ptr<PanelBase>> _tps, EditObject editObject) {};

    virtual bool IsClicked();

    virtual void DrawDebugPrint();

    bool GetIsClicked(PanelContent& panel);

    std::shared_ptr<PanelContent> _pobj;
   // virtual void SetPanel

	virtual void SetActive(bool flag);

};

