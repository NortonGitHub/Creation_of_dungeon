#ifndef SoundResource_h
#define SoundResource_h

#include "Resource.h"
#include <string>

class SoundResource : public Resource
{
public:
    SoundResource(std::string fileName);
    ~SoundResource();

    int GetHandle() const { return _handle; }
    
private:

    int _handle;
};

#endif /* SoundResource_h */
