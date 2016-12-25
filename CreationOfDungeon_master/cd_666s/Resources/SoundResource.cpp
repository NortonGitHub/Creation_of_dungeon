#include <stdio.h>
#include "SoundResource.h"
#include "DxLib.h"

SoundResource::SoundResource(std::string fileName)
    : Resource(fileName)
    , _handle(NULL)
{
    _handle = LoadSoundMem(fileName.c_str());
}


SoundResource::~SoundResource()
{
    DeleteSoundMem(_handle);
}