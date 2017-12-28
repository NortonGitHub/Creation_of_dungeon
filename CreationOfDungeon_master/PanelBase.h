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

    //PanelSettingObject��PanelAffectObjects�ɂ���Đ؂�ւ�����Ƃ��̂݌Ăяo�����
    //�݌v�I�ɖ�肪���肻��������e�X�g�Ł@�_�E���L���X�g����Ή���ł��邪�댯��
    virtual void PanelSettingObject_SettingPanel(std::string panelName, std::string GenerateText, std::string CategoryName, std::string graphName, int level, int LevelUpCost) {};

};

