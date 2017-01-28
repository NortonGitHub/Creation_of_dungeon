#ifndef ObjectInformationDrawer_h
#define ObjectInformationDrawer_h

#include "../../Vector2D.h"
#include "../Render/Sprite.h"
#include "../Sound/Sound.h"
#include "TiledObjectInformation.h"

class Character;

class ObjectInformationDrawer
{
public:
    ObjectInformationDrawer(const TiledObjectDictionary& iconDictionary);
    ~ObjectInformationDrawer();

    void Clear();
    void Init();
    void Update();
    void Draw();

private:

    void SetCharacter(Character* chara);
    void SetCharacter(Character* chara, Character* chara2);
    void SelectObject();

    Character* _character1, *_character2;
    TiledObjectInformation _thumbnail1, _thumbnail2;
    Sound _selectSE;
};

#endif /* ObjectInformationDrawer_h */
