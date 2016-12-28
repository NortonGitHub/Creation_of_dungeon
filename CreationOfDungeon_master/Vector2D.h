#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    Vector2D() : _x(0), _y(0){};
    Vector2D(double elemX, double elemY);
    Vector2D(double startX, double startY, double endX, double endY);
    Vector2D(const Vector2D &start, const Vector2D &end);
    ~Vector2D();
    
    inline void Set(const Vector2D &start, const Vector2D &end);
    inline void Set(double startX, double startY, double endX, double endY);
    inline void Set(double elemX, double elemY);
    
    const Vector2D operator+(const Vector2D &vec) const;
    const Vector2D operator+=(const Vector2D &vec);
    const Vector2D operator-(const Vector2D &vec) const;
    const Vector2D operator-=(const Vector2D &vec);
    const Vector2D operator*(const Vector2D &vec) const;
    const Vector2D operator*=(const Vector2D &vec);
    const Vector2D operator*(const double scale) const;
    const Vector2D operator*=(const double scale);
    const bool operator==(const Vector2D &vec) const;
    const bool operator!=(const Vector2D &vec) const;

    //ベクトルの長さを返す
    inline double GetLength() const;
    //ベクトル長の2乗を返す
    inline double GetSqLength() const;
    
    //ベクトルを正規化したものを返す
    inline Vector2D GetNormalized() const;
    //ベクトルを指定の角度(度数指定)回転させたものを返す
    inline Vector2D GetRotated(double theta) const;
    
    //ベクトルの各成分をvalue倍にする
    inline void Magnify(double value);
    //ベクトルを正規化する
    inline void Normalize();
    //ベクトルを視点を基点に,Z軸方向に指定の角度(度数指定)だけ回転させる
    inline void Rotate(double theta);
    //xとyを入れ替える
    inline void Swap();
    
    //内積値を算出
    inline static double Dot(const Vector2D &vecA, const Vector2D &vecB);
    //クロス積を出す
    inline static double Cross(const Vector2D &vecA, const Vector2D &vecB);
    
    //Z方向のベクトル(0, 0, 1)と3次元上で外積計算し、算出されたベクトルを取得
    //vec : 垂直を算出したいベクトル
    //useRightHandSystem : 右手系での正のZ座標の向きを使用するかどうか
    inline static Vector2D Cross(const Vector2D &vec, bool useRightHandSystem);
    
    //原点
    static const Vector2D zero;
    
    //カメラのUpベクトル基準で見たそれぞれの方向ベクトル
    static const Vector2D up;
    static const Vector2D left;
    static const Vector2D right;
    static const Vector2D down;
    
    double _x, _y;
};

#include "Vector2D_InlineDef.h"

#endif