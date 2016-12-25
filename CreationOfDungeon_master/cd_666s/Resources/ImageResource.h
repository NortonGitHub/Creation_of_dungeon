#ifndef ImageResource_h
#define ImageResource_h

#include "Resource.h"
#include "DxLib.h"

class ImageResource : public Resource
{
public:
    ImageResource(std::string fileName);    
    ~ImageResource();

    //GLuint GetID() const { return _id; }
    int GetHandle() const { return _handle; }
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    
private:

    int _handle;
    int _width;
    int _height;
};


#endif /* ImageResource_h */
