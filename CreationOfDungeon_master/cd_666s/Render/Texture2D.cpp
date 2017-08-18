#include <fstream>
#include <cassert>
#include "Texture2D.h"
#include "Camera.h"
#include "RenderManager.h"
#include "DxLib.h"

using namespace std;

Texture2D::Texture2D(int handle)
    : _handle(handle)
    , _scale(1, 1)
    , _usingUV_ul(0, 0)
    , _usingUV_lr(1, 1)
    , _isDisplaying(true)
    , _baseColor(1, 1, 1, 1)
    , _type(RenderType::DEFAULT)
    , _anchorType(AnchorType::CENTER)
    , _priority(0)
    , _angle(0)
{
}


Texture2D::~Texture2D()
{
}


void Texture2D::SetRenderType(RenderType type)
{
    RENDER_MGR->RemoveRenderModel(shared_from_this());
    _type = type;
    RENDER_MGR->AddRenderModel(shared_from_this());
}


void Texture2D::SetPriority(int priority)
{
    RENDER_MGR->ChangePriority(shared_from_this(), _priority, priority);
    _priority = priority;
}


void Texture2D::BuildTextureWithInit(int handle, int width, int height)
{
    _handle = handle;
    _baseSize.Set(_scale._x * width, _scale._y * height);
}


void Texture2D::BuildTexture(Vector2D pos, int width, int height)
{
    double Width  = width * _scale._x;
    double Height = height * _scale._y;
    
    _pos = pos;
    _baseSize.Set(Width, Height);
}


void Texture2D::BuildTexture(Vector2D pos, int width, int height, Vector2D scale)
{
    SetScale(scale);
    BuildTexture(pos, width, height);
}


void Texture2D::Render(const Camera& camera)
{
    if (_handle == NULL)
        return;

    if (!_isDisplaying)
        return;

    Vector2D pos = _pos + camera.GetPosition();

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_baseColor._a * 255));
    
    Vector2D pivot(_pos);
    Vector2D center(_pos);
    if (_anchorType == AnchorType::CENTER)
    {
        center = _baseSize * 0.5;
        pivot.Set(  _pos._x + _baseSize._x / 2 * _scale._x,
                    _pos._y + _baseSize._y / 2 * _scale._y);
    }

    DrawRotaGraph3F(
        static_cast<float>(pivot._x),
        static_cast<float>(pivot._y),
        static_cast<float>(center._x),
        static_cast<float>(center._y),
        _scale._x, 
        _scale._y, 
        _angle / 180 * DX_PI,
        _handle, true, false);
}