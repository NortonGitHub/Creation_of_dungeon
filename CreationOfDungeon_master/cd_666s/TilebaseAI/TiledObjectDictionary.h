#pragma once
#include <string>
#include <memory>
#include <vector>

class ImageResource;

class TiledObjectDictionary
{
    using ImageResourcePtr = std::shared_ptr<ImageResource>;
    using Record = std::pair<std::string, ImageResourcePtr>;

public:
    TiledObjectDictionary();
    ~TiledObjectDictionary();

    std::string GetIconNameFromName(std::string name) const;
    ImageResourcePtr GetImageFromName(std::string name) const;

private:

    void AddRecord(std::string name);
    std::vector<Record> _records;
};

