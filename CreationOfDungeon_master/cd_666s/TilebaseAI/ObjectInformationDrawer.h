#ifndef ObjectInformationDrawer_h
#define ObjectInformationDrawer_h

#include "../../Vector2D.h"
#include "../Render/Sprite.h"

class Character;

class ObjectInformationDrawer
{
public:
    ObjectInformationDrawer();
    ~ObjectInformationDrawer();
    
    void Init();
    void Update();
    void Draw();
    
private:
    
    void SetCharacter(Character* chara);
    void SetCharacter(Character* chara, Character* chara2);
    
    void SelectObject();
    void DrawCharactersInformation(Character* chara, Vector2D pos);

    Character* _character1, *_character2;

    Sprite _enemyThumbnail1, _enemyThumbnail2, _allyThumbnail1, _allyThumbnail2;
};

#endif /* ObjectInformationDrawer_h */