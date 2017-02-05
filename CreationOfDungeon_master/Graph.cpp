#include "Graph.h"
#include "DxLib.h"
#include <assert.h>

Graph::Graph()
    : _alpha(255)
    , _angle(0)
{
    _scale._x = 1.0;
    _scale._y = 1.0;
}


Graph::Graph(std::string fileName)
    : _alpha(255)
    , _angle(0)
{
    Load(fileName);

    //Šg‘å—¦‚Í1‚ÅŒÅ’è
    _scale._x = 1.0;
    _scale._y = 1.0;
}


Graph::Graph(std::string fileName, Vector2D point, Vector2D scale)
    : _alpha(255)
    , _angle(0)
    , _anchor(point)
{
    Load(fileName);
    SetGUIScale(scale);
}


Graph::~Graph()
{
    _imageResource = nullptr;
}


void Graph::Load(std::string fileName)
{
    //‰æ‘œ‚ð“Ç‚Ýž‚ÝA‰æ‘œƒTƒCƒY‚à“Ç‚Ýž‚Þ
    _imageResource = IMAGE_RESOURCE_TABLE->Create(fileName);

    assert((_imageResource->GetHandle() != -1) && "‰æ‘œ“Ç‚Ýž‚ÝŽ¸”s");

    _size.Set(_imageResource->GetWidth(), _imageResource->GetHeight());

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
    int handle = _imageResource->GetHandle();
    if (handle == NULL)
        return;

    DrawRotaGraph3F(
        static_cast<float>(_anchor._x + _size._x / 2 * _scale._x), 
        static_cast<float>(_anchor._y + _size._y / 2 * _scale._y),
        static_cast<float>(_size._x / 2), 
        static_cast<float>(_size._y / 2),
        _scale._x,
        _scale._y, 
        _angle * DX_PI,
        handle,
        true, 
        flip);
}
