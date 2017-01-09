#pragma once
#include <vector>
#include "../Render/Sprite.h"

class StartPoint;

class IntruderInfomation
{
public:
    IntruderInfomation();
    ~IntruderInfomation();

    void InitWithSetup(StartPoint* intrudePoint);
    void Update();
    void Draw();

private:

    Vector2D _position;
    StartPoint* _intrudePoint;
    std::vector<Sprite*> _icons;
};

