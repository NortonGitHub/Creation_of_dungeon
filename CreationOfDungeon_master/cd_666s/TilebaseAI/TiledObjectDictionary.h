#pragma once
#include <string>

class TiledObjectDictionary
{
public:
    TiledObjectDictionary();
    ~TiledObjectDictionary();

    std::string GetIconNameFromName(std::string name);
//    std::shared_ptr<ImageResoureece> GetImageFromName(std::string name);
};

