#ifndef MonsterController_h
#define MonsterController_h

#include "../../Vector2D.h"

class Monster;

class MonsterController
{
public:
    MonsterController();
    ~MonsterController();
    
    void Init();
    void Update();
    void Draw();

private:
    
    //–‚•¨‚Ì‘I‘ğ
    void SelectMonster(const Vector2D cursorPos);
    
    //–‚•¨‚Ì‘€ì
    void ControlMonster(const Vector2D cursorPos);
    
    //–‚•¨‚ÌŒˆ’è
    void SetControlingMonster(Monster* monster);
    
    //‘I‘ğ‚µ‚Ä‚¢‚é–‚•¨
    Monster* _monster;
    
};

#endif /* MonsterController_h */
