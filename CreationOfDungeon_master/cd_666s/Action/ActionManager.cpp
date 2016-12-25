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
    //�p�C�v���C���̓��e���X�V
    _actionPipelines.Update();
    
    for (size_t i=0; i < _actionPipelines._objects.size(); ++i)
    {
        //�A�N�V������1�t���[���i�߂�
        _actionPipelines._objects[i]->Update();
        
        //�������Ă�A�N�V�����̓p�C�v���C�����珜�� & �폜
        if (_actionPipelines._objects[i]->IsCompleted())
        {
            auto action = _actionPipelines._objects[i];
            delete action;
            action = nullptr;
        }
    }
}