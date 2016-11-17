#include "TrapManager.h"



TrapManager::TrapManager()
{
    traps.reserve(10);
}

TrapManager::TrapManager(std::string stage_num)
    : _name("trap")
{
}


TrapManager::~TrapManager()
{
    std::vector<TrapBase*>().swap(traps);
}

void TrapManager::Update()
{
}

void TrapManager::Draw()
{
}
