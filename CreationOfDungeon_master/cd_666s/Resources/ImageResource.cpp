#include "ImageResource.h"
#include "ResourceManager.h"
#include <assert.h>

ImageResource::ImageResource(std::string fileName)
    : Resource(fileName)
    , _handle(NULL)
{
    _handle = LoadGraph(fileName.c_str());

    int iWidth = 0;
    int iHeight = 0;
    GetGraphSize(_handle, &iWidth, &iHeight);
    _width = static_cast<double>(iWidth);
    _height = static_cast<double>(iHeight);
}

ImageResource::~ImageResource()
{
    DeleteGraph(_handle);
}