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
    
private:
    
    std::vector<AppearData> _appearData;
    std::vector<Enemy*> _restEnemyList;
    long _frameFromStart;
};

#endif /* StartPoint_h */
