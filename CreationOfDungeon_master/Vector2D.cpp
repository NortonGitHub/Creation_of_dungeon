#include "Vector2D.h"
#include <algorithm>
#include <math.h>

const Vector2D Vector2D::zero = Vector2D(double(0), double(0));
const Vector2D Vector2D::left = Vector2D(-1, 0);
const Vector2D Vector2D::right = Vector2D(1, 0);
const Vector2D Vector2D::down = Vector2D(0, 1);
const Vector2D Vector2D::up = Vector2D(0, -1);


Vector2D::Vector2D(double elemX, double elemY)
    : _x(elemX), _y(elemY)
{}


Vector2D::Vector2D(double startX, double startY, double endX, double endY)
    : _x(endX - startX), _y(endY - startY)
{}


Vector2D::Vector2D(const Vector2D &start, const Vector2D &end)
    : _x(end._x - start._x), _y(end._y - start._y)
{}


Vector2D::~Vector2D()
{}


const Vector2D Vector2D::operator+(const Vector2D &vec) const
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


const Vector2D Vector2D::operator-(const Vector2D &vec) const
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


const Vector2D Vector2D::operator*(const Vector2D &vec) const
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


const Vector2D Vector2D::operator*(const double scale) const
{
    Vector2D temp = *this;
    temp._x *= scale;
    temp._y *= scale;
    return std::move(temp);
}


const Vector2D Vector2D::operator*=(const double scale)
{
    _x *= scale;
    _y *= scale;
    return *this;
}


const bool Vector2D::operator==(const Vector2D &vec) const
{
    return (_x == vec._x && _y == vec._y);
}

const bool Vector2D::operator!=(const Vector2D &vec) const
{
    return (_x != vec._x || _y != vec._y);
}
