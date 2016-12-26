#include "Sprite.h"
#include "RenderManager.h"
#include "../Resources/ResourceManager.h"
#include <cassert>


Sprite::Sprite()
: _position(Vector2D::zero)
, _tex(nullptr)
{
}


Sprite::Sprite(std::string fileName, Vector2D pos)
    : _position(pos)
    , _tex(nullptr)
{
    Load(fileName);
}


Sprite::~Sprite()
{
    if (_textureResource == nullptr)
        return;
    
    //�`�惊�X�g����폜
    RENDER_MGR->RemoveRenderModel(_tex);

    delete _tex;
    _tex = nullptr;
    
    //���\�[�X���
    _textureResource = nullptr;
}


void Sprite::Load(std::string fileName)
{
    _textureResource = std::dynamic_pointer_cast<ImageResource>
    (RESOURCE_TABLE->Create(std::make_shared<ImageResource>(fileName)));
    
    if (_textureResource == nullptr)
        return;
    
    _tex = new Texture2D(_textureResource->GetHandle());
    _tex->BuildTexture(_position, _textureResource->GetWidth(), _textureResource->GetHeight());
    RENDER_MGR->AddRenderModel(_tex);
}


void Sprite::SetPosition(Vector2D pos)
{
    _position = pos;
    _tex->SetPosition(pos);
}


Vector2D Sprite::GetScale() const
{
    if (_tex == nullptr)
        return Vector2D::zero;
    
    return _tex->GetScale();
}


void Sprite::SetScale(Vector2D scale)
{
    if (_tex != nullptr)
    {
        auto size =_tex->GetSize();
        _tex->BuildTexture(_position, size._x, size._y, scale);
    }
};


void Sprite::LookAt(Vector2D dir)
{
    auto t = dir._y / dir.GetLength();
    auto tt = dir._x / dir.GetLength();
    auto rad = acos(t);
    
    if (asin(tt) > 0)
        rad *= -1.0;

    auto theta = rad / 3.141592 * 180;
    Rotate(theta);
}