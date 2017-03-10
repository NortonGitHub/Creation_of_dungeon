#pragma once
#include <vector>
#include "../Render/Sprite.h"

class GraphicalObject
{
public:
    GraphicalObject();
    virtual ~GraphicalObject();

    virtual void Update();
    virtual void Draw();

    Vector2D GetPosition() const { return _position; }
    virtual bool Contain(Vector2D pos) const;

protected:

    Vector2D _position;
    Sprite _graph;
};

