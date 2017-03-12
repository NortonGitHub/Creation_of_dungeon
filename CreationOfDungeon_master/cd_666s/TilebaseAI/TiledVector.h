#pragma once
#define TILE_SIZE TiledVector::_tileSize
#define TILE_SCALE (TiledVector::_tileSize / 32.0)
#define FIELD_OFFSET_X TiledVector::_fieldOffsetX
#define FIELD_OFFSET_Y TiledVector::_fieldOffsetY

#include "../../Vector2D.h"

class TiledVector
{
public:
    TiledVector() : _x(0), _y(0){};
    TiledVector(int elemX, int elemY);
    TiledVector(int startX, int startY, int endX, int endY);
    TiledVector(const TiledVector &start, const TiledVector &end);
    ~TiledVector();
    
    inline void Set(const TiledVector &start, const TiledVector &end)
    {
        _x = end._x - start._x;
        _y = end._y - start._y;
    }
    
    inline void Set(int startX, int startY, int endX, int endY)
    {
        _x = endX - startX;
        _y = endY - startY;
    }
    
    inline void Set(int elemX, int elemY)
    {
        _x = elemX;
        _y = elemY;
    }
    
    const TiledVector operator+(const TiledVector &vec) const;
    const TiledVector operator+=(const TiledVector &vec);
    const TiledVector operator-(const TiledVector &vec) const;
    const TiledVector operator-=(const TiledVector &vec);
    const TiledVector operator*(const TiledVector &vec) const;
    const TiledVector operator*=(const TiledVector &vec);
    const TiledVector operator*(const int scale) const;
    const TiledVector operator*=(const int scale);
    const bool operator==(const TiledVector &vec) const;
    const bool operator!=(const TiledVector &vec) const;
    
    enum Direction
    {
        LEFT = 0,
        FORWARD = 1,
        RIGHT = 2,
        BACK = 3
    };
    
    //directionの方向へ回転させる
    void Rotate(Direction direction);
    //directionの方向へ回転させたものを得る
    TiledVector GetRotated(Direction direction) const;
    
    //Bresenhamアルゴリズムでの長さを得る
    int GetBresenhamLength(bool diagonal) const;
    
    static TiledVector ConvertToTiledPos(Vector2D pos);
    Vector2D GetWorldPos() const { return std::move(Vector2D(_x * TILE_SIZE + FIELD_OFFSET_X, _y * TILE_SIZE + FIELD_OFFSET_Y)); }

    
    //原点
    static const TiledVector zero;
    
    //カメラのUpベクトル基準で見たそれぞれの方向ベクトル
    static const TiledVector up;
    static const TiledVector left;
    static const TiledVector right;
    static const TiledVector down;
    
    //周囲4/8マスのオフセットをまとめた配列
    static const TiledVector fourDirecton[4];
    static const TiledVector eightDirecton[8];
    
    int _x, _y;

    static int _tileSize;
    static int _fieldOffsetX;
    static int _fieldOffsetY;
};

