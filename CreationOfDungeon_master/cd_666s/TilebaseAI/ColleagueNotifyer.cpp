#include "ColleagueNotifyer.h"
#include "Character.h"

ColleagueNotifyer::ColleagueNotifyer()
{
}


ColleagueNotifyer::~ColleagueNotifyer()
{
}


void ColleagueNotifyer::Update()
{
    _removes.clear();
    _removes.resize(0);
}


void ColleagueNotifyer::AddColleague(Character& obj)
{
    _colleagues.push_back(&obj);
}


void ColleagueNotifyer::RemoveColleague(Character& obj)
{
    auto it = std::find(_colleagues.begin(), _colleagues.end(), &obj);
    _colleagues.erase(it);
}


void ColleagueNotifyer::NotifyRemoveTarget(TiledObject& obj)
{
    for (auto chara : _colleagues)
    {
        if (chara->_target == nullptr)
            continue;
        
        if (chara->_target->IsEnable())
            continue;
        
        //削除されるオブジェクトを対象にしていたら、諦めるようにする
        chara->ResetTarget();
    }
    
    _removes.push_back(&obj);
}


bool ColleagueNotifyer::IsChasable(const TiledObject& target) const
{
    //削除予定のオブジェクトなら
    for (auto obj : _removes)
    {
        //"登録できない"と返す
        if (obj == &target)
            return false;
    }
    
    return true;
}
