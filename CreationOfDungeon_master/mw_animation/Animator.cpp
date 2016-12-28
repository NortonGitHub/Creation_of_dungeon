#include "Animator.h"


Animator::Animator()
{
}


Animator::~Animator()
{
}

//再生するアニメ―ション切り替え
void Animator::Switch(std::string animationName)
{
    _animation = _animations[animationName];
    _currentName = animationName;
}

//アニメを切り替え、直前のアニメを最初の状態へ
void Animator::SwitchWithReset(std::string animationName)
{
    auto temp = _animation;

    //多重再生防止
    if (temp == _animations[animationName])
        return;
    else
    {
        //直前のアニメーションをスタート位置へ
        temp->SetCurrentTime(0);
    }

    _animation = _animations[animationName];
    _currentName = animationName;
}

void Animator::AddAnimation(std::string name, std::shared_ptr<GraphArray> animation)
{
    _animations.insert(std::make_pair(name, animation));
}

void Animator::RemoveAnimation(std::string animationName)
{
    auto removeAnimation = _animations[animationName];

    //指定のアニメが無ければ終了
    if (removeAnimation == nullptr)
        return;

    //現在再生中のアニメーションと同じだと、終了
    if (_animations[animationName] == _animation)
        return;
}

void Animator::Update()
{
    _animation->Update();
}

/*
void Animator::Draw(const Vector2D vec, bool flip)
{
    _animation->_graphPtr->Draw(vec, flip);
}
*/