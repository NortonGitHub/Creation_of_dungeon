#pragma once
#include "Vector2D.h"

class MouseContent {
public:
    MouseContent() :_pos(0, 0),
        _mouse_left_click(false),
        _mouse_right_click(false),
        _mouse_left_press(false),
        _mouse_right_press(false),
        _mouse_middle_click(false),
        _mouse_middle_press(false)
    {
    };
    ~MouseContent() {};

    Vector2D _pos;  //ç¿ïW

    bool _mouse_left_click;
    bool _mouse_right_click;
    bool _mouse_middle_click;

    bool _mouse_left_press;
    bool _mouse_right_press;
    bool _mouse_middle_press;
};