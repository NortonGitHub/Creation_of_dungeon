#ifndef Action_h
#define Action_h

#include <vector>
#include <functional>

/*
 _actions.push_back(
	[&](int frame)
	{
        //����Ȋ����Ŏ��Ԃ�p�����֐��ɂ��g����
        func(frame);
	}
 );
 */

class Action
{
public:
    
    //�A�N�V�����𐶐����ăp�C�v���C���ɓo�^����
    //tips:�߂�l�̓A�N�V�����I�u�W�F�N�g�̃|�C���^
    static Action* CreateAction(int interval, std::function<void(int)> action, bool playWithStart = true);
    static Action* CreateAction(int interval, std::vector<std::function<void(int)>> actions, bool playWithStart = true);

    //�A�N�V���������̏�ŏI�����ăp�C�v���C������폜����.
    //tips:�����ɓn�����I�u�W�F�N�g��delete�����.
    //tips:�폜�ɐ�������Ɩ߂�l��nullptr�ɂȂ�.
    static Action* DeleteAction(Action *action);
 
    ~Action();
    
    //�A�N�V�������I��������
    bool IsCompleted() const { return (_currentAction == _actions.end()); }
    
    //�A�N�V�������Đ������ǂ���
    bool IsPlaying() const { return _isPlaying; }
    
    //�t���[���J�E���g�ƃA�N�V�����X�V
    void Update();

    
    //�A�N�V�������ꎞ��~����
    void Stop() { _isPlaying = false; };
    //�A�N�V��������~���Ă����ꍇ�A�ĊJ����
    void Play() { _isPlaying = true; };
    
    bool GetLoopFlag() const { return _isLoop; }
    void SetLoopFlag(bool flag) { _isLoop = flag; }
    
private:

    //Create�֐��ȊO�ł̃C���X�^���X������h�~
    Action(int interval, std::function<void(int)> action, bool playWithStart = true);
    Action(int interval, std::vector<std::function<void(int)>> actions, bool playWithStart = true);
    
    struct SimpleAction
    {
        SimpleAction(int interval, std::function<void(int)> action)
            : _actionInterval(interval)
            , _actionFrame(0)
            , _action(std::move(action))
        {}
        
        std::function<void(int)> _action;
        
        //�A�N�V������������
        int _actionInterval;
        
        //�A�N�V�����o�ߎ���
        int _actionFrame;
    };
    
    bool _isLoop;
    bool _isPlaying;
    std::vector<SimpleAction> _actions;
    std::vector<SimpleAction>::iterator _currentAction;
};


#endif /* Action_h */
