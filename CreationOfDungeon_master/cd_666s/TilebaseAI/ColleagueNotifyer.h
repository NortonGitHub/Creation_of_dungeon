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
    
    //‚»‚Ì‘ÎÛ‚ğ’Ç‚¤•K—v‚ª‚ ‚é‚©‚Ç‚¤‚©
    bool IsChasable(const TiledObject& target) const;

    int GetColleagues() const { return _colleagues.size(); }
    
private:
    
    std::vector<Character *> _colleagues;
    std::vector<TiledObject *> _removes;
};

#endif /* ColleagueNotifyer_h */
