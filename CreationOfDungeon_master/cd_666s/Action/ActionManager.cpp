#include "ActionManager.h"


ActionManager::ActionManager()
{
}


ActionManager::~ActionManager()
{
    _actionPipelines.Clear();
}


void ActionManager::AddAction(Action* action)
{
    _actionPipelines.Add(action);
}


void ActionManager::RemoveAction(Action* action)
{
    _actionPipelines.Remove(action);
}


void ActionManager::Update()
{
    //パイプラインの内容を更新
    _actionPipelines.Update();
    
    for (size_t i=0; i < _actionPipelines._objects.size(); ++i)
    {
        //アクションを1フレーム進める
        _actionPipelines._objects[i]->Update();
        
        //完了してるアクションはパイプラインから除去 & 削除
        if (_actionPipelines._objects[i]->IsCompleted())
        {
            auto action = _actionPipelines._objects[i];
            delete action;
            action = nullptr;
        }
    }
}