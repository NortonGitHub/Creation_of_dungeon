#include "SummonsManager.h"



SummonsManager::SummonsManager()
{
    summons.reserve(10);
}

SummonsManager::SummonsManager(std::string stage_num)
    : _name("summons")
{
}


SummonsManager::~SummonsManager()
{
    std::vector<SummonsBase*>().swap(summons);
}

void SummonsManager::Update()
{
}

void SummonsManager::Draw()
{
}
