#include "ImageResource.h"
#include <assert.h>

ImageResource::ImageResource(std::string fileName)
    : Resource(fileName)
    , _handle(NULL)
{
    static int totalID = 1;
    totalID++;

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