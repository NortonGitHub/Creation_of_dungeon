#pragma once
#include "CharaManagerBase.h"
#include "MonsterBase.h"

class MonsterManager :
    public CharaManagerBase
{
public:
    MonsterManager();
    MonsterManager(std::string stage_num);
    ~MonsterManager();

    void Update();
    void Draw();

    std::string GetManagerName() const { return _name; }

private:
    std::vector<MonsterBase*> monsters;
    std::string _name;
};

