#include "Action.h"
#include "ActionManager.h"

Action::Action(int interval, std::function<void(int)> action, bool playWithStart)
    : _isPlaying(playWithStart)
    , _isLoop(false)
{
    SimpleAction simpleAction(interval, action);
    _actions.push_back(std::move(simpleAction));
    _currentAction = _actions.begin();
    ACTION_MGR->AddAction(this);
}


Action::Action(int interval, std::vector<std::function<void(int)>> actions, bool playWithStart)
    : _isPlaying(playWithStart)
    , _isLoop(false)
{
    for (size_t i=0; i<actions.size(); ++i)
    {
        SimpleAction simpleAction(interval, actions[i]);
        _actions.push_back(std::move(simpleAction));
    }
        
    _currentAction = _actions.begin();
    ACTION_MGR->AddAction(this);
}


Action* Action::DeleteAction(Action* action)
{
    if (action != nullptr)
    {
        delete action;
        action = nullptr;
    }
    
    return action;
}


Action::~Action()
{
    ACTION_MGR->RemoveAction(this);
}


Action* Action::CreateAction(int interval, std::function<void(int)> action, bool playWithStart)
{
    Action* argAction = new Action(interval, std::move(action));
    return argAction;
}


Action* Action::CreateAction(int interval, std::vector<std::function<void(int)>> actions, bool playWithStart)
{
    Action* argAction = new Action(interval, std::move(actions));
    return argAction;
}


void Action::Update()
{
    if (!_isPlaying)
        return;
    
    if (IsCompleted())
        return;
    
    //�A�N�V������1�t���[���i�߂�
    auto action =  _currentAction;
    action->_action(action->_actionFrame);
    action->_actionFrame++;
    
    //�K�莞�ԂɒB�����玟�̃A�N�V������
    if (action->_actionInterval < action->_actionFrame)
    {
        if (_currentAction != _actions.end())
        {
            //���[�v����Ȃ�J�E���^�����������Ă���
            if (_isLoop)
                action->_actionFrame = 0;
            
            _currentAction++;
        }
        
        //�Ō�܂œ��B���A���[�v����Ȃ�ŏ��̃A�N�V������
        if (_isLoop
            && _currentAction == _actions.end())
            _currentAction = _actions.begin();
        
    }
}
