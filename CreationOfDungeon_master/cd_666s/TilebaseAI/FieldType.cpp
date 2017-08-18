#include "FieldType.h"
#include "../Resources/AllResourceManager.h"
/*
std::string GetMapChipGraphDirectory(FieldType type)
{
    std::string directory = IMAGE_RESOURCE_TABLE->GetFolderPath();
    switch (type)
    {
    case FieldType::Cave:
        directory += "cave/";
        break;

    case FieldType::Forest:
        directory += "forest/";
        break;
    }

    return directory;
}


FieldType GetFieldTypeFromData(std::string data)
{
    if (data.find("#FST") != std::string::npos)
        return FieldType::Cave;

    if (data.find("#CAV") != std::string::npos)
        return FieldType::Cave;

    return FieldType::None;
}
*/