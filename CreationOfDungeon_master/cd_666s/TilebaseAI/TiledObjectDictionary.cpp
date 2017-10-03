#include "TiledObjectDictionary.h"
#include "../Resources/ImageResource.h"


TiledObjectDictionary::TiledObjectDictionary()
{
    AddRecord("magician");
    AddRecord("blaver");
    AddRecord("fighter");
    AddRecord("thief");
    AddRecord("healer");
    AddRecord("minotaur");
    AddRecord("bone");
    AddRecord("ghost");
    AddRecord("slime");
}


TiledObjectDictionary::~TiledObjectDictionary()
{
    _records.clear();
}


std::string TiledObjectDictionary::GetIconNameFromName(std::string name) const
{
    for (auto& record : _records)
    {
        if (name == record.first)
            return record.second->GetName();
    }

    return "";
}


TiledObjectDictionary::ImageResourcePtr TiledObjectDictionary::GetImageFromName(std::string name) const 
{
    for (auto& record : _records)
    {
        if (name == record.first)
            return record.second;
    }

    return nullptr;
}


void TiledObjectDictionary::AddRecord(std::string name)
{
    std::string folderPath = "resourse/graph/tiledObject/";
    std::string format = ".png";

    auto record = std::make_pair(name, std::make_shared<ImageResource>(folderPath + name + format));
    _records.push_back(std::move(record));
}