#pragma once
#include "../Render/Sprite.h"

class Character;

class TiledObjectInformation
{
public:
    TiledObjectInformation(Vector2D position = Vector2D::zero);
    ~TiledObjectInformation();

    void SetPosition(Vector2D pos) { _position = pos; }
    void SetCharacter(Character* chara) { _character = chara; };

    void Init();
    void Clear();
    void Draw();

private:

    void DrawInformation(Character* chara);

    Vector2D _position;
    Sprite _enemyThumbnail, _allyThumbnail;
    std::vector<Sprite*> _icon;
    Character* _character;
};

