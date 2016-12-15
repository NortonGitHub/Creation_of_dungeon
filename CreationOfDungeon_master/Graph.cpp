#include "Graph.h"
#include "ResourceLoader.h"
#include "DxLib.h"
#include <assert.h>

Graph::Graph()
    : _handle(NULL)
    , _alpha(255)
    , _angle(0)
{
    _scale._x = 1.0;
    _scale._y = 1.0;
}


Graph::Graph(std::string fileName)
    : _handle(NULL)
    , _alpha(255)
    , _angle(0)
{
    Load(fileName);

    //拡大率は1で固定
    _scale._x = 1.0;
    _scale._y = 1.0;
}


Graph::Graph(std::string fileName, Vector2D point, Vector2D scale)
    : _handle(NULL)
    , _alpha(255)
    , _angle(0)
    , _anchor(point)
{
    Load(fileName);
    SetGUIScale(scale);
}


Graph::~Graph()
{
    DeleteGraph(_handle);
}


void Graph::Load(std::string fileName)
{
    //画像を読み込み、画像サイズも読み込む
    _handle = ResourceLoader::Load(fileName.c_str());

    assert((_handle != -1) && "画像読み込み失敗");

    int sizeX = 0;
    int sizeY = 0;
    GetGraphSize(_handle, &sizeX, &sizeY);

    _size.Set(sizeX, sizeY);

    _alpha = 255;
    _angle = 0;
}


void Graph::SetGUIScale(double argWidth, double argHeight)
{
    _scale._x = argWidth;
    _scale._y = argHeight;
}


void Graph::Draw(bool flip)
{
    if (_handle == NULL)
        return;

    DrawRotaGraph3F(
        static_cast<float>(_anchor._x + _size._x / 2 * _scale._x), 
        static_cast<float>(_anchor._y + _size._y / 2 * _scale._y),
        static_cast<float>(_size._x / 2), 
        static_cast<float>(_size._y / 2),
        _scale._x,
        _scale._y, 
        _angle * DX_PI,
        _handle, 
        true, 
        flip);
}
