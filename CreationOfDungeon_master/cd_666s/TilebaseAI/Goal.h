#ifndef Goal_h
#define Goal_h

#include "TiledObject.h"

class Character;
class ColleagueNotifyer;

class Goal : public TiledObject
{
public:
    Goal(TiledVector tilePos, ColleagueNotifyer& notifyer);
    ~Goal();
    
    bool IsOverwritable(TiledObject* overwriter) override;

    void Init() override;
    void Update() override;
    void Draw() override;
    void Interact(Character& chara) override;
    
    //�ʉ߂��Ă��܂�������Ԃ�(�����GameOver����ł���)
    int GetPassedNum() const { return _passedNum; }
    
private:
    
    //���n��̃L�����Ԃŏ�񋤗L���邽�߂̒ʐM�@
    ColleagueNotifyer& _notifyer;
    
    int _passedNum;
};

#endif /* Goal_h */
