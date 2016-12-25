#ifndef MonsterController_h
#define MonsterController_h

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
    void SelectMonster();
    
    //–‚•¨‚Ì‘€ì
    void ControlMonster();
    
    //–‚•¨‚ÌŒˆ’è
    void SetControlingMonster(Monster* monster);
    
    //‘I‘ğ‚µ‚Ä‚¢‚é–‚•¨
    Monster* _monster;
    
};

#endif /* MonsterController_h */
