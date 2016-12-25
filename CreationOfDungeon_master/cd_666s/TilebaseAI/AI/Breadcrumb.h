#pragma once
#include "../TiledVector.h"

class Breadcrumb
{
public:
    Breadcrumb(TiledVector tile, int lifeTime);
    ~Breadcrumb();

    void Update();
    void Draw();

    int GetID() const { return _id; };
    TiledVector GetTilePos() const { return _pos; }

private:

    int _id;
    int _time;
    int _lifeTime;

    TiledVector _pos;
};

