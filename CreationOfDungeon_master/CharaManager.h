#pragma once
#include <vector>
#include "CharaBase.h"
#include "CharaManagerBase.h"
#include "MouseContent.h"

class CharaManager
{
public:
    CharaManager();
    CharaManager(std::string stage_num);
    ~CharaManager();

    void Update(MouseContent mc);
    void Draw();

private:
    //std::vector<CharaBase*> character;
    
    std::vector<CharaManagerBase*> chara;
};

