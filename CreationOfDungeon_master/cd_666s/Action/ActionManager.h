#ifndef ActionManager_h
#define ActionManager_h

#include "../Utility/Singleton.h"
#include "../Utility/PoolingSystem.h"
#include "Action.h"

class ActionManager : public Singleton<ActionManager>
{
public:
    ActionManager();
    ~ActionManager();
    
    void AddAction(Action* action);
    void RemoveAction(Action* action);

    //�A�N�V�����𒆎~���p�C�v���C���ꗗ�����菜��
    void QuitAction(Action* action);
    void Update();
    
private:

    PoolingSystem<Action>_actionPipelines;
};

#define ACTION_MGR ActionManager::GetInstance()

#endif /* ActionManager_h */
