#pragma once

class EnemyAIBase
{
public:
    EnemyAIBase();
    virtual ~EnemyAIBase();

    virtual void Reset() = 0;
    virtual void Update() = 0;
    virtual void Draw();
    
private:

};

