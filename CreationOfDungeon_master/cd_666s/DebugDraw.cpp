#include "DebugDraw.h"
#include "DxLib.h"
#include "Render/RenderManager.h"
#include <functional>

namespace Debug
{

    void DrawLine(Vector2D start, Vector2D end, Color4 color)
    {
        RENDER_MGR->AddDebugCall(new Line(start, end, color));
    }

    void DrawLine(float startX, float startY, float endX, float endY, Color4 color)
    {
        RENDER_MGR->AddDebugCall(new Line(startX, startY, endX, endY, color));
    }

    void DrawLineDirectly(Vector2D start, Vector2D end, Color4 color)
    {
        Debug::DrawLineDirectly(static_cast<float>(start._x),
            static_cast<float>(start._y),
            static_cast<float>(end._x),
            static_cast<float>(end._y),
            color);
    }

    void DrawLineDirectly(float startX, float startY, float endX, float endY, Color4 color)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(color._a * 255));

        DxLib::DrawLine(
            static_cast<int>(startX), static_cast<int>(startY),
            static_cast<int>(endX), static_cast<int>(endY),
            GetColor(color._r * 255, color._g * 255, color._b * 255));

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }



    void DrawCircle(Vector2D center, float radius, Color4 color, bool fill)
    {
        RENDER_MGR->AddDebugCall(new Circle(center, radius, color, fill));
    }

    void DrawCircle(float x, float y, float radius, Color4 color, bool fill)
    {
        RENDER_MGR->AddDebugCall(new Circle(x, y, radius, color, fill));
    }

    void DrawCircleDirectly(Vector2D center, float radius, Color4 color, bool fill)
    {
        Debug::DrawCircleDirectly(static_cast<float>(center._x),
            static_cast<float>(center._y),
            radius, color, fill);
    }

    void DrawCircleDirectly(float x, float y, float radius, Color4 color, bool fill)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(color._a * 255));

        DxLib::DrawCircle(static_cast<int>(x), static_cast<int>(y),
            static_cast<int>(radius),
            GetColor(color._r * 255, color._g * 255, color._b * 255)
            , fill);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }



    void DrawRectWithPoint(Vector2D lowerLeft, Vector2D upperRight, Color4 color, bool fill)
    {
        RENDER_MGR->AddDebugCall(new RectWithPoint(lowerLeft, upperRight, color, fill));
    }

    void DrawRectWithPoint(float minX, float minY, float maxX, float maxY, Color4 color, bool fill)
    {
        RENDER_MGR->AddDebugCall(new RectWithPoint(minX, minY, maxX, maxY, color, fill));
    }

    void DrawRectWithPointDirectly(Vector2D lowerLeft, Vector2D upperRight, Color4 color, bool fill)
    {
        Debug::DrawRectWithPointDirectly(static_cast<float>(lowerLeft._x),
            static_cast<float>(lowerLeft._y),
            static_cast<float>(upperRight._x),
            static_cast<float>(upperRight._y),
            color,
            fill);
    }

    void DrawRectWithPointDirectly(float minX, float minY, float maxX, float maxY, Color4 color, bool fill)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(color._a * 255));

        DrawBox(static_cast<int>(minX), 
            static_cast<int>(minY),
            static_cast<int>(maxX), 
            static_cast<int>(maxY),
            GetColor(color._r * 255, color._g * 255, color._b * 255), fill);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }



    void DrawRectWithSize(Vector2D lowerLeft, Vector2D size, Color4 color, bool fill)
    {
        RENDER_MGR->AddDebugCall(new RectWithSize(lowerLeft, size, color, fill));
    }

    void DrawRectWithSize(float x, float y, float width, float height, Color4 color, bool fill)
    {
        RENDER_MGR->AddDebugCall(new RectWithSize(x, y, width, height, color, fill));
    }

    void DrawRectWithSizeDirectly(Vector2D lowerLeft, Vector2D size, Color4 color, bool fill)
    {
        Debug::DrawRectWithPointDirectly(
            static_cast<float>(lowerLeft._x),
            static_cast<float>(lowerLeft._y),
            static_cast<float>(lowerLeft._x + size._x),
            static_cast<float>(lowerLeft._y + size._y),
            color,
            fill);
    }

    void DrawRectWithSizeDirectly(float x, float y, float width, float height, Color4 color, bool fill)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(color._a * 255));

        DrawBox(static_cast<int>(x), 
            static_cast<int>(y),
            static_cast<int>(x + width), 
            static_cast<int>(y + height),
            GetColor(color._r * 255, color._g * 255, color._b * 255),
            fill);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }



    void DrawString(Vector2D pos, std::string str, Color4 color)
    {
        RENDER_MGR->AddDebugCall(new String(pos, str, color));
    }

    void DrawStringDirectly(Vector2D pos, std::string str, Color4 color)
    {
        DrawFormatString(
            static_cast<int>(pos._x), 
            static_cast<int>(pos._y), 
            GetColor(color._r * 255, color._g * 255, color._b * 255)
            , str.c_str());
    }


    Line::Line(Vector2D start, Vector2D end, Color4 color)
        : _start(start), _end(end), _color(color) {}

    Line::Line(double startX, double startY, double endX, double endY, Color4 color)
        : _start(Vector2D(startX, startY)), _end(Vector2D(endX, endY)), _color(color) {}

    void Line::Draw()
    {
        DrawLineDirectly(_start, _end, _color);
    }



    Circle::Circle(Vector2D center, float radius, Color4 color, bool fill)
        : _center(center), _radius(radius), _color(color), _fill(fill) {}

    Circle::Circle(double x, double y, float radius, Color4 color, bool fill)
        : _center(Vector2D(x, y)), _radius(radius), _color(color), _fill(fill) {}

    void Circle::Draw()
    {
        DrawCircleDirectly(_center, _radius, _color, _fill);
    }



    RectWithSize::RectWithSize(Vector2D lowerLeft, Vector2D size, Color4 color, bool fill)
    : _lowerLeft(lowerLeft), _size(size), _color(color), _fill(fill) {}

    RectWithSize::RectWithSize(double x, double y, double width, double height, Color4 color, bool fill)
        : _lowerLeft(Vector2D(x, y)), _size(Vector2D(width, height)), _color(color), _fill(fill) {}

    void RectWithSize::Draw()
    {
        DrawRectWithSizeDirectly(_lowerLeft, _size, _color, _fill);
    }


    RectWithPoint::RectWithPoint(Vector2D lowerLeft, Vector2D upperRight, Color4 color, bool fill)
        : _lowerLeft(lowerLeft), _upperRight(upperRight), _color(color), _fill(fill) {}

    RectWithPoint::RectWithPoint(double minX, double minY, double maxX, double maxY, Color4 color, bool fill)
        : _lowerLeft(Vector2D(minX, minY)), _upperRight(Vector2D(maxX, maxY)), _color(color), _fill(fill) {}

    void RectWithPoint::Draw()
    {
        DrawRectWithPointDirectly(_lowerLeft, _upperRight, _color, _fill);
    }


    String::String(Vector2D pos, std::string str, Color4 color)
        : _pos(pos), _str(str), _color(color) {}

    void String::Draw()
    {
        DrawStringDirectly(_pos, _str, _color);
    }
}