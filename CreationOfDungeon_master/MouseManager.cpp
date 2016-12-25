#include "DxLib.h"
#include "MouseManager.h"

MouseContent MouseManager::GetMouseStatus(MouseContent before)
{
    MouseContent mc;

    mc._pos = GetMousePos();

    mc._mouse_left_click = IsClicked("left", before._mouse_left_click);
    mc._mouse_right_click = IsClicked("right", before._mouse_right_click);
    mc._mouse_middle_click = IsClicked("middle", before._mouse_middle_click);

    mc._mouse_left_press = IsPressed("left");
    mc._mouse_right_press = IsPressed("right");
    mc._mouse_middle_press = IsPressed("middle");

    return mc;
}

Vector2D MouseManager::GetMousePos()
{
    Vector2D _pos;
    int mouse_x;
    int mouse_y;

    GetMousePoint(&mouse_x, &mouse_y);
    _pos.Set(mouse_x, mouse_y);

    return _pos;
}
/*
クリックしたか否かを調べる
引数
button  : どちらのボタンを押したか
"left"  : 左
"right" : 右
"middle": 中心
*/
bool MouseManager::IsClicked(std::string button, bool before_flag)
{
    int mb = GetMouseInput();
    if (before_flag)
        return false;

    if (button == "left") {
        return ((mb & MOUSE_INPUT_LEFT) == 1);
    }
    else if (button == "right") {
        return ((mb & MOUSE_INPUT_RIGHT) == 1);
    }
    else if (button == "middle") {
        return ((mb &  MOUSE_INPUT_MIDDLE) == 1);
    }

    return      false;
}

/*
ボタンを押されてるか否かを調べる
引数
button  : どちらのボタンを押したか
"left"  : 左
"right" : 右
"middle": 中心
*/
bool MouseManager::IsPressed(std::string button)
{
    int mb = GetMouseInput();

    if (button == "left") {
        return ((mb & MOUSE_INPUT_LEFT) == 1);
    }
    else if (button == "right") {
        return ((mb & MOUSE_INPUT_RIGHT) == 1);
    }
    else if (button == "middle") {
        return ((mb &  MOUSE_INPUT_MIDDLE) == 1);
    }

    return  false;
}

bool MouseManager::OnMouseOver(MouseContent mc, Vector2D pos1, Vector2D pos2)
{
    return IsOnMouse(mc._pos, pos1, pos2);
}

bool MouseManager::OnMouseOver(Vector2D mc, Vector2D pos1, Vector2D pos2)
{
    return IsOnMouse(mc, pos1, pos2);
}

bool MouseManager::IsOnMouse(Vector2D mc, Vector2D pos1, Vector2D pos2)
{
    return (mc._x >= pos1._x) && (mc._x <= pos2._x)
        && (mc._y >= pos1._y) && (mc._y <= pos2._y);
}
