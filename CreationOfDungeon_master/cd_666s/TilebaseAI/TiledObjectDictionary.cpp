#include "TiledObjectDictionary.h"



TiledObjectDictionary::TiledObjectDictionary()
{
}


TiledObjectDictionary::~TiledObjectDictionary()
{
}


std::string TiledObjectDictionary::GetIconNameFromName(std::string name)
{
    if (name == "magician")
        return "resourse/graph/tiledObject/magician.png";

    if (name == "blaver")
        return "resourse/graph/tiledObject/blaver.png";

    if (name == "fighter")
        return "resourse/graph/tiledObject/fighter.png";

    if (name == "minotaur")
        return "resourse/graph/tiledObject/minotaur.png";

    if (name == "bone")
        return "resourse/graph/tiledObject/bone.png";

    if (name == "ghost")
        return "resourse/graph/tiledObject/ghost.png";

    return "";
}