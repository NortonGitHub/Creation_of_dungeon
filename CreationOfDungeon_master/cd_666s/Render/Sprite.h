#ifndef Sprite_h
#define Sprite_h

#include "Texture2D.h"
#include "../Resources/ImageResource.h"
#include <string>
#include <memory>

class Sprite
{
public:
    Sprite();
    Sprite(std::string fileName, Vector2D pos = Vector2D::zero);
    ~Sprite();

    Vector2D GetPosition() const { return _position; }
    Vector2D GetScale() const;

    void SetPosition(Vector2D pos);
    void SetScale(Vector2D scale);
    void SetBaseColor(Color4 color){ if(_tex != nullptr) _tex->SetBaseColor(color); }
    void SetDisplayMode(bool isDisplaying) { if (_tex != nullptr) _tex->SetDisplayMode(isDisplaying); }
    void SetPriority(int priority) { if (_tex != nullptr) _tex->SetPriority(priority); }

    Texture2D* GetTexturePtr() { return _tex; }
    
    void Load(std::string fileName);
    
    void Rotate(double angle) { if (_tex != nullptr) _tex->_angle = angle; }
    void LookAt(Vector2D dir);
    

protected:
    
    std::shared_ptr<ImageResource> _textureResource;
    Texture2D *_tex;
    Vector2D _position;
};

#endif /* Sprite_h */
