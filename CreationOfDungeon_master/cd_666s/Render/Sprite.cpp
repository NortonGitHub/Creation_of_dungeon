#include "Sprite.h"
#include "RenderManager.h"
#include "../Resources/ResourceManager.h"
#include <cassert>


Sprite::Sprite()
: _position(Vector2D::zero)
, _tex(nullptr)
{
    _tex = std::make_shared<Texture2D>(NULL);
    RENDER_MGR->AddRenderModel(_tex);
}


Sprite::Sprite(std::string fileName, Vector2D pos)
    : _position(pos)
    , _tex(nullptr)
{
    _tex = std::make_shared<Texture2D>(NULL);
    Load(fileName);
    RENDER_MGR->AddRenderModel(_tex);
}


Sprite::~Sprite()
{
    if (_tex != nullptr)
    {
        //描画リストから削除
        RENDER_MGR->RemoveRenderModel(_tex);
    }

    _tex = nullptr;
    
    //リソース解放
    _textureResource = nullptr;
}


void Sprite::SetResource(std::shared_ptr<ImageResource> resource)
{
    _textureResource = resource;
    if (_textureResource == nullptr)
    {
        _tex->BuildTextureWithInit(NULL, 1, 1);
    }
    else
    {
        _tex->BuildTextureWithInit(_textureResource->GetHandle(), _textureResource->GetWidth(), _textureResource->GetHeight());
    }
}


void Sprite::Load(std::string fileName)
{
    _textureResource = IMAGE_RESOURCE_TABLE->Create(IMAGE_RESOURCE_TABLE->GetFolderPath() + fileName);
    if (_textureResource == nullptr)
    {
        _tex->BuildTexture(_position, 1, 1);
    }
    else
    {
        _tex->SetPosition(_position);
        _tex->BuildTextureWithInit(_textureResource->GetHandle(), _textureResource->GetWidth(), _textureResource->GetHeight());
    }
}


void Sprite::SetPosition(Vector2D pos)
{
    if (_tex != nullptr)
    {
        _position = pos;
        _tex->SetPosition(pos);
    }
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
