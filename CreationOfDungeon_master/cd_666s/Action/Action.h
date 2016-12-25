#ifndef Action_h
#define Action_h

#include <vector>
#include <functional>

/*
 _actions.push_back(
	[&](int frame)
	{
        //こんな感じで時間を用いた関数にも使える
        func(frame);
	}
 );
 */

class Action
{
public:
    
    //アクションを生成してパイプラインに登録する
    //tips:戻り値はアクションオブジェクトのポインタ
    static Action* CreateAction(int interval, std::function<void(int)> action, bool playWithStart = true);
    static Action* CreateAction(int interval, std::vector<std::function<void(int)>> actions, bool playWithStart = true);

    //アクションをその場で終了してパイプラインから削除する.
    //tips:引数に渡したオブジェクトはdeleteされる.
    //tips:削除に成功すると戻り値はnullptrになる.
    static Action* DeleteAction(Action *action);
 
    ~Action();
    
    //アクションが終了したか
    bool IsCompleted() const { return (_currentAction == _actions.end()); }
    
    //アクションを再生中かどうか
    bool IsPlaying() const { return _isPlaying; }
    
    //フレームカウントとアクション更新
    void Update();

    
    //アクションを一時停止する
    void Stop() { _isPlaying = false; };
    //アクションが停止していた場合、再開する
    void Play() { _isPlaying = true; };
    
    bool GetLoopFlag() const { return _isLoop; }
    void SetLoopFlag(bool flag) { _isLoop = flag; }
    
private:

    //Create関数以外でのインスタンス生成を防止
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
        
        //アクション持続時間
        int _actionInterval;
        
        //アクション経過時間
        int _actionFrame;
    };
    
    bool _isLoop;
    bool _isPlaying;
    std::vector<SimpleAction> _actions;
    std::vector<SimpleAction>::iterator _currentAction;
};


#endif /* Action_h */
