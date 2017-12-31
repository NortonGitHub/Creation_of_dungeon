#ifndef StartPoint_h
#define StartPoint_h

#include "TiledObject.h"
#include "MessageManager.h"
#include <vector>

class MessageReciever;
class Enemy;

class StartPoint : public TiledObject
{
    typedef std::pair<std::weak_ptr<Enemy>, long> AppearData;
public:
    StartPoint(TiledVector tilePos, MessageReciever& reciever);
    StartPoint(TiledVector tilePos);
    ~StartPoint();
    
    bool IsOverwritable(TiledObject* overwriter) override;

    void Init() override;
    void Update() override;
    void Draw() override;
    
    void AddToAppearList(std::weak_ptr<Enemy> enemy, long appearFrame);
    
    Character* GetNextEnemy();

    //Ÿ‚Ì“G‚ªoŒ»‚·‚é‚Ü‚Å
    int GetTimeUnitlNext() const;

    //“G‚ª‚à‚¤‚¢‚È‚¢‚±‚Æ‚ğ•\‚·”’l
    static constexpr int NobodyIntruder() { return -1; }

	int GetTimeUnitNextFrom() const;

private:
    
    std::vector<AppearData> _appearData;
    long _frameFromStart;

    size_t _currentIndex;

    MessageReciever& _reciever;
    TalkDatabase _intrudeMessage;

	bool _isGetFirstTime;
};

#endif /* StartPoint_h */
