#pragma once
#include "CharaManagerBase.h"
#include "SummonsBase.h"

class SummonsManager :
    public CharaManagerBase
{
public:
    SummonsManager();
    SummonsManager(std::string stage_num);
    ~SummonsManager();

    void Update();
    void Draw();

    std::string GetManagerName() const { return _name; }

private:
    std::vector<SummonsBase*> summons;
    std::string _name;
};

