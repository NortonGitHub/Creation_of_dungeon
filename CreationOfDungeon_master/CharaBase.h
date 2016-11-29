#pragma once

#include "Vector2D.h"
#include <string>
#include <memory>

class CharaBase
{
public:
    CharaBase();

    CharaBase(std::string _chara_num) {
        chara_num = _chara_num;
    }

    virtual ~CharaBase();

    virtual void Update() = 0;
    virtual void Draw() = 0;

#if 0
    virtual CharaManagerBase* GetManagerInstance() = 0;
#endif

private:
    std::string chara_num;

    
};

