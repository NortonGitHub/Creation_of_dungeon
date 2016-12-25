#pragma once
#include "Vector2D.h"
#include <algorithm>
#include <math.h>

//ベクトルの各成分をvalue倍にする
void Vector2D::Magnify(double value)
{
    _x *= value;
    _y *= value;
}

void Vector2D::Normalize()
{
    double length = GetLength();
    
    if (length <= 0.0001)
    {
        _x = 0;
        _y = 0;
        return;
    }
    
    _x /= length;
    _y /= length;
}

//ベクトルを指定の角度だけ回転させる
void Vector2D::Rotate(double theta)
{
    double length = GetLength();
    
    if (length <= 0.0001)
    {
        _x = 0;
        _y = 0;
        return;
    }
    
    //現在のx軸(1, 0)との角度を算出
    //b = (1, 0)
    //cos = (a.x * b.x + a.y * b.y) / (|a| * |b|)
    // = a.x / a.length
    double rad = acos(_x / length);
    
    //acos値だけでは時計・反時計まわりが判別できないので
    //asin値もとって確認
    //sin = a.y / a.length
    if (asin(_y / length) < 0)
        rad *= -1.0;
    
    //現在の角度からさらに回転させる
    //theta += rad;
    _x = length * cos(rad + theta * (3.14159265359 / 180.0));
    _y = length * sin(rad + theta * (3.14159265359 / 180.0));
}

void Vector2D::Swap()
{
    std::swap(_x, _y);
}

void Vector2D::Set(const Vector2D &start, const Vector2D &end)
{
    _x = end._x - start._x;
    _y = end._y - start._y;
}

void Vector2D::Set(double elemX, double elemY)
{
    _x = elemX;
    _y = elemY;
}

void Vector2D::Set(double startX, double startY, double endX, double endY)
{
    _x = endX - startX;
    _y = endY - startY;
}

double Vector2D::GetLength() const
{
    return sqrt(_x * _x + _y * _y);
}

double Vector2D::GetSqLength() const
{
    return (_x * _x + _y * _y);
}

//内積値を算出
double Vector2D::Dot(const Vector2D &vecA, const Vector2D &vecB)
{
    return (vecA._x * vecB._x + vecA._y * vecB._y);
}

//クロス積を出す
double Vector2D::Cross(const Vector2D &vecA, const Vector2D &vecB)
{
    return (vecA._x * vecB._y - vecA._y * vecB._x);
}

//Z方向のベクトル(0, 0, 1)と3次元上で外積計算し、算出されたベクトルを取得
Vector2D Vector2D::Cross(const Vector2D &vecA, bool useRightHandSystem)
{
    //Vector3 c = (0, 0, 1) と交差判定
    double z = (useRightHandSystem) ? 1.0 : -1.0;
    
    //bx = ay * cz - cy * az = ay * cz;
    //by = az * cy - cz * ax = -cz * ax;
    //bz = ay * cx - cy * ax = 0;
    
    return std::move(Vector2D(vecA._y * z, -vecA._x * z));
}

Vector2D Vector2D::GetNormalized() const
{
    Vector2D temp(_x, _y);
    temp.Normalize();
    
    return std::move(temp);
}

Vector2D Vector2D::GetRotated(double theta) const
{
    Vector2D temp(_x, _y);
    temp.Rotate(theta);
    
    return std::move(temp);
}