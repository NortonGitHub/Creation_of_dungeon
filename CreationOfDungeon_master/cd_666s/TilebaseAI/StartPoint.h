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

    //次の敵が出現するまで
    int GetTimeUnitlNext() const;

private:
    
    std::vector<AppearData> _appearData;
    long _frameFromStart;

    size_t _currentIndex;
};

#endif /* StartPoint_h */
