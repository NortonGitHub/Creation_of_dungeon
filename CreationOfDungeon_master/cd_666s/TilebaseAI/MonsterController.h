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
    
    //�����̑I��
    void SelectMonster();
    
    //�����̑���
    void ControlMonster();
    
    //�����̌���
    void SetControlingMonster(Monster* monster);
    
    //�I�����Ă��閂��
    Monster* _monster;
    
};

#endif /* MonsterController_h */
