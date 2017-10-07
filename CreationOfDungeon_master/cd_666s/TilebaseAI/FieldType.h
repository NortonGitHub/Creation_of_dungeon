#pragma once
#include <string>
#include "../Resources/AllResourceManager.h"

enum class FieldType
{
    Cave = 0,
    Forest,
    Stone,

    None
};

static std::string GetMapChipGraphDirectory(FieldType type) 
{
    std::string directory = "resource/graph/background/";
    switch (type)
    {
    case FieldType::Cave:
        directory += "cave/";
        break;

    case FieldType::Forest:
        directory += "forest/";
        break;

    case FieldType::Stone:
        directory += "stone/";
        break;

    }

    return directory;
}

static FieldType GetFieldTypeFromData(std::string data)
{
    if (data.find("#FST") != std::string::npos)
        return FieldType::Forest;

    if (data.find("#CAV") != std::string::npos)
        return FieldType::Cave;

    if (data.find("#STN") != std::string::npos)
        return FieldType::Stone;

    return FieldType::None;
}