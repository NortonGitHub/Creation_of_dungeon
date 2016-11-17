#include "HeroBase.h"


HeroBase::HeroBase()
{

#if 0
    manager = new HeroManager();
#endif
}


HeroBase::~HeroBase()
{
}

bool HeroBase::IsDefeated(int _hp)
{
    if (_hp <= 0)
        return true;
    else
        return false;
}
