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
    
    //その対象を追う必要があるかどうか
    bool IsChasable(const TiledObject& target) const;

    int GetColleagues() const { return _colleagues.size(); }
    
private:
    
    std::vector<Character *> _colleagues;
    std::vector<TiledObject *> _removes;
};

#endif /* ColleagueNotifyer_h */
