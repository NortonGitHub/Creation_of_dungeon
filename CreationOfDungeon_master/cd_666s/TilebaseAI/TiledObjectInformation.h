#pragma once
#include "../Render/Sprite.h"
#include "TiledObjectDictionary.h"

class Character;

class TiledObjectInformation
{
public:
    TiledObjectInformation(const TiledObjectDictionary& iconDictionary, Vector2D position = Vector2D::zero);
    ~TiledObjectInformation();

    void SetPosition(Vector2D pos) { _position = pos; }
    void SetCharacter(Character* chara) { _character = chara; };

    void Init();
    void Clear();
    void Draw();

private:

    const TiledObjectDictionary& _iconDictionary;

    Sprite _enemyThumbnail, _allyThumbnail;

    std::unique_ptr<Sprite> _icon;
    Vector2D _position;
    Character* _character;
};

