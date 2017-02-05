#pragma once

#include <memory>
#include <utility>
#include <string>

#include "cd_666s/Resources//ResourceManager.h"
#include "Vector2D.h"

/*
簡易的に利用可能な画像クラス
*/

class Graph
{
    friend class GraphArray;

public:

    //すべて初期値に設定して何もしない
    Graph();

    //自動で画像を読み込む
    Graph(std::string fileName);

    //自動で画像を読み込み、描画位置と位置指定つき
    Graph(std::string fileName, Vector2D point, Vector2D scale = Vector2D(1, 1));

    ~Graph();

    //ファイル名をもとに画像を読み込む
    void Load(std::string fileName);

    //画像の拡大率を設定
    void SetGUIScale(double argWidth, double argHeight);
    void SetGUIScale(Vector2D scale) { _scale = scale; };

    //描画の基準位置を設定
    void SetPosition(Vector2D pos) { _anchor = pos; }

    void Draw(bool flip = false);
 
    //画像の拡大率を取得
    Vector2D GetGUIScale() const { return _scale; }

    //元画像のピクセルサイズを取得
    Vector2D GetGUISize() const { return _size; }

    //元画像のピクセルサイズ * 拡大率　で算出される
    //画像を拡大した際のサイズを取得
    Vector2D GetSize() const
    {
        return Vector2D(_size._x * _scale._x, _size._y * _scale._y);
    }

private:

    //画像の基本サイズ
    Vector2D _size;

    //拡大率
    Vector2D _scale;

    //オフセット値(0, 0でオブジェクトの左上座標)
    Vector2D offset;

    //描画の基準位置
    Vector2D _anchor;

    std::shared_ptr<ImageResource> _imageResource;

    //透明度
    int _alpha;

    double _angle;
};
