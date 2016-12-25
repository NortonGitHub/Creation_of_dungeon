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
    RENDER_MGR->RemoveRenderModel(this);
    _type = type;
    RENDER_MGR->AddRenderModel(this);
}


void Texture2D::SetPriority(int priority)
{
    RENDER_MGR->ChangePriority(this, _priority, priority);
    _priority = priority;
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
    if (!_isDisplaying)
        return;

    Vector2D pos = _pos + camera.GetPosition();

    DrawRotaGraph3F(
        static_cast<float>(_pos._x + _baseSize._x / 2 * _scale._x), 
        static_cast<float>(_pos._y + _baseSize._y / 2 * _scale._y),
        static_cast<float>(_baseSize._x / 2),
        static_cast<float>(_baseSize._x / 2),
        _scale._x, 
        _scale._y, 
        _angle * DX_PI,
        _handle, true, false);

    /*
    glTranslatef(_pos._x, _pos._y, 0);
    glRotatef(_angle, 0, 0, 1.0);

    DrawGraphF(, , _handle, true);
    DrawRect

    if (_anchorType == AnchorType::CENTER)
    {
        glTexCoord2d(_usingUV_ul._x, _usingUV_lr._y);
        glVertex3d(- _baseSize._x / 2, - _baseSize._y / 2, 0.0);
        glTexCoord2d(_usingUV_lr._x, _usingUV_lr._y);
        glVertex3d(  _baseSize._x / 2, - _baseSize._y / 2, 0.0);
        glTexCoord2d(_usingUV_lr._x, _usingUV_ul._y);
        glVertex3d(  _baseSize._x / 2,   _baseSize._y / 2, 0.0);
        glTexCoord2d(_usingUV_ul._x, _usingUV_ul._y);
        glVertex3d(- _baseSize._x / 2,   _baseSize._y / 2, 0.0);

        D
    }
    else if (_anchorType == AnchorType::LOWER_LEFT)
    {
        glTexCoord2d(_usingUV_ul._x, _usingUV_lr._y);
        glVertex3d(0.0, 0.0, 0.0);
        glTexCoord2d(_usingUV_lr._x, _usingUV_lr._y);
        glVertex3d(_baseSize._x, 0.0, 0.0);
        glTexCoord2d(_usingUV_lr._x, _usingUV_ul._y);
        glVertex3d(_baseSize._x, _baseSize._y, 0.0);
        glTexCoord2d(_usingUV_ul._x, _usingUV_ul._y);
        glVertex3d(0.0, _baseSize._y, 0.0);
    }
    
    glRotatef(-_angle, 0, 0, 1.0);
    glTranslatef(-_pos._x, -_pos._y, 0);
    */
}