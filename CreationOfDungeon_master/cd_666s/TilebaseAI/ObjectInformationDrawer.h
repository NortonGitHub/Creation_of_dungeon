#ifndef ObjectInformationDrawer_h
#define ObjectInformationDrawer_h

#include "../../Vector2D.h"
#include "../Render/Sprite.h"
#include "../Sound/Sound.h"

class Character;

class ObjectInformationDrawer
{
public:
    ObjectInformationDrawer();
    ~ObjectInformationDrawer();

    void Clear();
    void Init();
    void Update();
    void Draw();

    // TODO :あとでもっと楽に共有アクセスできるようにする
    static int GetIndexFromName(std::string name);
    static std::string GetIconNameFromName(std::string name);

private:

    void SetCharacter(Character* chara);
    void SetCharacter(Character* chara, Character* chara2);

    void SelectObject();
    void DrawCharactersInformation(Character* chara, Vector2D pos);

    Character* _character1, *_character2;

    Sprite _enemyThumbnail1, _enemyThumbnail2, _allyThumbnail1, _allyThumbnail2;
    std::vector<Sprite*> _icon1, _icon2;
    Sound _selectSE;
};

#endif /* ObjectInformationDrawer_h */
