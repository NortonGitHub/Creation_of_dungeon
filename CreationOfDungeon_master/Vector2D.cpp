#include "Vector2D.h"
#include "DxLib.h"
#include <math.h>
#include <algorithm>

const Vector2D Vector2D::zero = Vector2D(double(0), double(0));

Vector2D::Vector2D(double x, double y)
    : _x(x),
    _y(y)
{
}

Vector2D::Vector2D(double ax, double ay, double bx, double by)
    : _x(ax - bx),
    _y(bx - by)
{
}

Vector2D::~Vector2D()
{
}

void Vector2D::Set(double x, double y)
{
    _x = x;
    _y = y;
}

void Vector2D::Set(double ax, double ay, double bx, double by)
{
    _x = ax - bx;
    _y = ay - by;
}

void Vector2D::Rotate(double theta)
{
    double length = GetLength();

    _x = length * cos(theta * (DX_PI / 180));
    _y = length * sin(theta * (DX_PI / 180));
}

void Vector2D::Scale(double scale)
{
    _x *= scale;
    _y *= scale;
}

double Vector2D::GetLength()
{
    return sqrt(_x*_x + _y*_y);
}

Vector2D Vector2D::GetRotated(double theta)
{
    Vector2D temp(_x, _y);
    temp.Rotate(theta);
    return std::move(temp);
}

Vector2D Vector2D::GetScaled(double scale)
{
    Vector2D temp(_x, _y);
    temp.Scale(scale);
    return std::move(temp);
}

const Vector2D Vector2D::operator=(const Vector2D & vec)
{
    Vector2D temp = *this;
    temp._x = vec._x;
    temp._y = vec._y;
    return std::move(temp);
}

const Vector2D Vector2D::operator+(const Vector2D &vec)
{
    Vector2D temp = *this;
    temp._x += vec._x;
    temp._y += vec._y;
    return std::move(temp);
}

const Vector2D Vector2D::operator+=(const Vector2D &vec)
{
    _x += vec._x;
    _y += vec._y;
    return *this;
}

const Vector2D Vector2D::operator-(const Vector2D &vec)
{
    Vector2D temp = *this;
    temp._x -= vec._x;
    temp._y -= vec._y;
    return std::move(temp);
}

const Vector2D Vector2D::operator-=(const Vector2D &vec)
{
    _x -= vec._x;
    _y -= vec._y;
    return *this;
}

const Vector2D Vector2D::operator*(const Vector2D &vec)
{
    Vector2D temp = *this;
    temp._x *= vec._x;
    temp._y *= vec._y;
    return std::move(temp);
}

const Vector2D Vector2D::operator*=(const Vector2D &vec)
{
    _x *= vec._x;
    _y *= vec._y;
    return *this;
}

const Vector2D Vector2D::operator*(const double scale)
{
    Vector2D temp = *this;
    temp._x *= scale;
    temp._y *= scale;
    return std::move(temp);
}

const Vector2D Vector2D::operator*=(const  double scale)
{
    _x *= scale;
    _y *= scale;
    return *this;
}

const bool Vector2D::operator==(const Vector2D & vec)
{
    return (vec._x == _x) && (vec._y == _y);
}

const bool Vector2D::operator!=(const Vector2D & vec)
{
    return (vec._x != _x) && (vec._y != _y);
}

