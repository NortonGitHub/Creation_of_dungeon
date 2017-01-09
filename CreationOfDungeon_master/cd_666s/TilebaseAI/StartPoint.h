#ifndef StartPoint_h
#define StartPoint_h

#include "TiledObject.h"
#include <vector>

class Enemy;

class StartPoint : public TiledObject
{
    typedef std::pair<Enemy *, long> AppearData;
public:
    StartPoint(TiledVector tilePos);
    ~StartPoint();
    
    bool IsOverwritable(TiledObject* overwriter) override;

    void Init() override;
    void Update() override;
    void Draw() override;
    
    void AddToAppearList(Enemy* enemy, long appearFrame);
    
    Character* GetNextEnemy();

    //Ÿ‚Ì“G‚ªoŒ»‚·‚é‚Ü‚Å
    int GetTimeUnitlNext() const;

    //“G‚ª‚à‚¤‚¢‚È‚¢‚±‚Æ‚ğ•\‚·”’l
    static constexpr int NobodyIntruder() { return -1; }

private:
    
    std::vector<AppearData> _appearData;
    long _frameFromStart;

    size_t _currentIndex;
};

#endif /* StartPoint_h */
