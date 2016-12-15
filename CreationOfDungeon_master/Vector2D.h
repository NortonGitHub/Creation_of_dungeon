#pragma once
class Vector2D
{
public:
    Vector2D() : _x(0), _y(0) {};
    Vector2D(double x, double y);
    Vector2D(double ax, double ay, double bx, double by);
    ~Vector2D();

    const Vector2D operator+(const Vector2D &vec);
    const Vector2D operator+=(const Vector2D &vec);
    const Vector2D operator-(const Vector2D &vec);
    const Vector2D operator-=(const Vector2D &vec);
    const Vector2D operator*(const Vector2D &vec);
    const Vector2D operator*=(const Vector2D &vec);
    const Vector2D operator*(const double scale);
    const Vector2D operator*=(const double scale);
    const bool operator==(const Vector2D &vec);
    const bool operator!=(const Vector2D &vec);


    void Set(double x, double y);
    void Set(double ax, double ay, double bx, double by);

    void Rotate(double theta);
    void Scale(double scale);

    double GetLength();
    Vector2D GetRotated(double theta);
    Vector2D GetScaled(double scale);

    static const Vector2D zero;
    static const Vector2D up;
    static const Vector2D left;
    static const Vector2D right;
    static const Vector2D down;

    /*座標・幅(縦横)を兼ねた変数*/
    /*宣言したVector2D型変数ごとに用途を変更すること*/
    double _x, _y;
};

