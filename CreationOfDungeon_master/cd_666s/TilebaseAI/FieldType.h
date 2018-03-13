#pragma once
#include <string>
#include "../Resources/AllResourceManager.h"

enum class FieldType
{
    Cave = 0,
    Forest,
    Stone,
	Timber,

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

	case FieldType::Timber:
		directory += "wood/";
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

	if (data.find("#TIM") != std::string::npos)
		return FieldType::Timber;

    return FieldType::None;
}