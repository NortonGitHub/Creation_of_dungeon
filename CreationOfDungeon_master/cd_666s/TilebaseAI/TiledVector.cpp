#include "TiledVector.h"
#include <algorithm>
#include <math.h>

const TiledVector TiledVector::zero = TiledVector(int(0), int(0));
const TiledVector TiledVector::left = TiledVector(-1, 0);
const TiledVector TiledVector::right = TiledVector(1, 0);
const TiledVector TiledVector::down = TiledVector(0, -1);
const TiledVector TiledVector::up = TiledVector(0, 1);
const TiledVector TiledVector::fourDirecton[4] = { TiledVector::left, TiledVector::up, TiledVector::right, TiledVector::down };
const TiledVector TiledVector::eightDirecton[8] =
{
    TiledVector::left, TiledVector::up, TiledVector::right, TiledVector::down,
    TiledVector(-1, -1), TiledVector(1, -1), TiledVector(1, 1), TiledVector(-1, 1)
};

int TiledVector::_tileSize = 32;
int TiledVector::_fieldOffsetX = 172;
int TiledVector::_fieldOffsetY = 68;

TiledVector::TiledVector(int elemX, int elemY)
    : _x(elemX), _y(elemY)
{}


TiledVector::TiledVector(int startX, int startY, int endX, int endY)
    : _x(endX - startX), _y(endY - startY)
{}


TiledVector::TiledVector(const TiledVector &start, const TiledVector &end)
    : _x(end._x - start._x), _y(end._y - start._y)
{}


TiledVector::~TiledVector()
{}


const TiledVector TiledVector::operator+(const TiledVector &vec) const
{
    TiledVector temp = *this;
    temp._x += vec._x;
    temp._y += vec._y;
    return std::move(temp);
}


const TiledVector TiledVector::operator+=(const TiledVector &vec)
{
    _x += vec._x;
    _y += vec._y;
    return *this;
}


const TiledVector TiledVector::operator-(const TiledVector &vec) const
{
    TiledVector temp = *this;
    temp._x -= vec._x;
    temp._y -= vec._y;
    return std::move(temp);
}


const TiledVector TiledVector::operator-=(const TiledVector &vec)
{
    _x -= vec._x;
    _y -= vec._y;
    return *this;
}


const TiledVector TiledVector::operator*(const TiledVector &vec) const
{
    TiledVector temp = *this;
    temp._x *= vec._x;
    temp._y *= vec._y;
    return std::move(temp);
}


const TiledVector TiledVector::operator*=(const TiledVector &vec)
{
    _x *= vec._x;
    _y *= vec._y;
    return *this;
}


const TiledVector TiledVector::operator*(const int scale) const
{
    TiledVector temp = *this;
    temp._x *= scale;
    temp._y *= scale;
    return std::move(temp);
}


const TiledVector TiledVector::operator*=(const int scale)
{
    _x *= scale;
    _y *= scale;
    return *this;
}


const bool TiledVector::operator==(const TiledVector &vec) const
{
    return (_x == vec._x && _y == vec._y);
}


const bool TiledVector::operator!=(const TiledVector &vec) const
{
    return (_x != vec._x || _y != vec._y);
}


int TiledVector::GetBresenhamLength(bool diagonal) const
{
    int x = std::abs(_x);
    int y = std::abs(_y);

    //ŽÎ‚ßˆÚ“®‚ð‹–—e‚µ‚Ä‚¢‚é‚È‚ç
    if (diagonal)
    {
        return (x < y) ? y : x;
    }
    
    //‚»‚¤‚Å‚È‚¢‚È‚çcˆÚ“® + ‰¡ˆÚ“®
    return x + y;
}


void TiledVector::Rotate(Direction direction)
{
    //”½‘ÎŒü‚«‚É‚·‚é‚È‚ç
    if (direction == Direction::BACK)
    {
        *this *= -1;
        return;
    }

    int scale = GetBresenhamLength(false);
    TiledVector normalized = *this * (1 / scale);

    //¶‚É‰ñ“]‚·‚é‚È‚ç
    if (direction == Direction::LEFT)
    {
        for (size_t i = 3; 0 <= i; --i)
        {
            //Še•ûŒü‚ÌƒxƒNƒgƒ‹‚Æ’l‚ªˆê’v‚·‚é‚Ü‚ÅŒJ‚è•Ô‚·
            if (normalized == TiledVector::fourDirecton[i])
            {
                if (i == 0)
                    i = 4;

                normalized = TiledVector::fourDirecton[i - 1];
                break;
            }
        }
    }
    //‰E‚É‰ñ“]‚·‚éê‡‚à“¯“™
    else if (direction == Direction::RIGHT)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            if (normalized == TiledVector::fourDirecton[i])
            {
                if (i == 3)
                    i = -1;

                normalized = TiledVector::fourDirecton[i + 1];
                break;
            }
        }
    }

    _x = normalized._x * scale;
    _y = normalized._y * scale;
}


TiledVector TiledVector::GetRotated(Direction direction) const
{
    TiledVector temp = *this;
    temp.Rotate(direction);
    return temp;
}


TiledVector TiledVector::ConvertToTiledPos(Vector2D pos)
{
     pos -= Vector2D(FIELD_OFFSET_X, FIELD_OFFSET_Y);
     return std::move(TiledVector(pos._x / TILE_SIZE, pos._y / TILE_SIZE));
}