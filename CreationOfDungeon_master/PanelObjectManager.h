#pragma once
#include "./cd_666s/Utility/Singleton.h"
#include "EditMap.h"
#include "PanelBase.h"

class PanelObjectManager :
    public Singleton<PanelObjectManager>
{
    friend class EditMap;
public:
    PanelObjectManager();
    ~PanelObjectManager();

    void Add(std::shared_ptr<PanelBase> obj);
    void Remove(const PanelBase* obj);

    void Clear();
    void Refresh();

    std::vector<std::shared_ptr<PanelBase>> _objects;

private:
    bool _needRefresh;
    std::vector<const PanelBase*> _deleteOrders;
    std::vector<std::shared_ptr<PanelBase>> _addOrders;
};

#define PANEL_MGR PanelObjectManager::GetInstance()

