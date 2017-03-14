#ifndef DebugDraw_h
#define DebugDraw_h

#include <cmath>
#include <string>
#include "../Vector2D.h"
#include "Color.h"

namespace Debug
{
    void DrawLine(Vector2D start, Vector2D end, Color4 color);
    void DrawLine(float startX, float startY, float endX, float endY, Color4 color);
    void DrawLineDirectly(Vector2D start, Vector2D end, Color4 color);
    void DrawLineDirectly(float startX, float startY, float endX, float endY, Color4 color);


    void DrawCircle(Vector2D center, float radius, Color4 color, bool fill);
    void DrawCircle(float x, float y, float radius, Color4 color, bool fill);
    void DrawCircleDirectly(Vector2D center, float radius, Color4 color, bool fill);
    void DrawCircleDirectly(float x, float y, float radius, Color4 color, bool fill);

    void DrawRectWithPoint(Vector2D lowerLeft, Vector2D upperRight, Color4 color, bool fill);
    void DrawRectWithPoint(float minX, float minY, float maxX, float maxY, Color4 color, bool fill);
    void DrawRectWithPointDirectly(Vector2D lowerLeft, Vector2D upperRight, Color4 color, bool fill);
    void DrawRectWithPointDirectly(float minX, float minY, float maxX, float maxY, Color4 color, bool fill);

    void DrawRectWithSize(Vector2D lowerLeft, Vector2D size, Color4 color, bool fill);
    void DrawRectWithSize(float x, float y, float width, float height, Color4 color, bool fill);
    void DrawRectWithSizeDirectly(Vector2D lowerLeft, Vector2D size, Color4 color, bool fill);
    void DrawRectWithSizeDirectly(float x, float y, float width, float height, Color4 color, bool fill);

    void DrawString(Vector2D pos, std::string str, Color4 color = ColorPalette::BLACK4, int size = 16);
    void DrawStringDirectly(Vector2D pos, std::string str, Color4 color, int size = 16);

    //デバッグ描画を行う関数のオブジェクト
    class DebugDraw 
    {
    public: 
        virtual ~DebugDraw() {};
        virtual void Draw() = 0; 
    };

    //直線デバッグ描画
    class Line : public DebugDraw
    {
    public:
        Line(Vector2D start, Vector2D end, Color4 color);
        Line(double startX, double startY, double endX, double endY, Color4 color);
        ~Line() {}
        void Draw() override;

    private:
        Vector2D _start, _end;
        Color4 _color;
    };

    //円デバッグ描画
    class Circle : public DebugDraw
    {
    public:
        Circle(Vector2D center, float radius, Color4 color, bool fill);
        Circle(double x, double y, float radius, Color4 color, bool fill);
        void Draw() override;

    private:
        Vector2D _center;
        float _radius;
        Color4 _color;
        bool _fill;
    };

    //DxLib:左上(OpenGL:左下)座標 + サイズ指定の矩形デバッグ描画
    class RectWithSize : public DebugDraw
    {
    public:
        RectWithSize(Vector2D lowerLeft, Vector2D size, Color4 color, bool fill);
        RectWithSize(double x, double y, double width, double height, Color4 color, bool fill);
        void Draw() override;

    private:
        Vector2D _lowerLeft, _size;
        Color4 _color;
        bool _fill;
    };

    //X, Y軸の最小値と最大値指定の矩形デバッグ描画
    class RectWithPoint : public DebugDraw
    {
    public:
        RectWithPoint(Vector2D lowerLeft, Vector2D upperRight, Color4 color, bool fill);
        RectWithPoint(double minX, double minY, double maxX, double maxY, Color4 color, bool fill);
        void Draw() override;

    private:
        Vector2D _lowerLeft, _upperRight;
        Color4 _color;
        bool _fill;
    };

    //デバッグ文字列描画
    class String : public DebugDraw
    {
    public:
        String(Vector2D pos, std::string str, Color4 color, int size);
        void Draw() override;

    private:
        Vector2D _pos;
        std::string _str;
        Color4 _color;
        int _fontSize;
    };
};

#endif /* DebugDraw_h */
