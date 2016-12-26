#ifndef ColleagueNotifyer_h
#define ColleagueNotifyer_h

#include <vector>

class Character;
class TiledObject;

class ColleagueNotifyer
{
public:
    ColleagueNotifyer();
    ~ColleagueNotifyer();
    
    void AddColleague(Character& obj);
    void RemoveColleague(Character& obj);
    void NotifyRemoveTarget(TiledObject& obj);

    void Update();
    
    //���̑Ώۂ�ǂ��K�v�����邩�ǂ���
    bool IsChasable(TiledObject& target);
    
    //�S�ł��Ă��邩�ǂ���
    bool HasWipeouted() const;
    
private:
    
    std::vector<Character *> _colleagues;
    std::vector<TiledObject *> _removes;
};

#endif /* ColleagueNotifyer_h */