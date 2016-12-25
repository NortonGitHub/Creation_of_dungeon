#pragma once
#include <string>
#include "Vector2D.h"
#include "MouseContent.h"
#include "ControllerBase.h"

class MouseManager :
    public ControllerBase
{
public:
    MouseManager(const MouseManager&) = delete;

    static MouseManager& GetInstance() {
        static MouseManager m;
        return m;
    };

    static MouseContent GetMouseStatus(MouseContent before);
    static Vector2D GetMousePos();

    static bool IsClicked(std::string button, bool before_flag);
    static bool IsPressed(std::string button);

    static bool OnMouseOver(MouseContent mc,Vector2D pos1, Vector2D pos2);
    static bool OnMouseOver(Vector2D mc, Vector2D pos1, Vector2D pos2);

private:
    MouseManager() = default;
    ~MouseManager() = default;

    static bool IsOnMouse(Vector2D mc, Vector2D pos1, Vector2D pos2);

};

