#include "Resource.h"
#include "ResourceManager.h"

Resource::Resource(std::string fileName)
: _fileName(fileName)
{
}

Resource::~Resource()
{
}

bool Resource::Load()
{
    return false;
}

bool Resource::Unload()
{
    return false;
}