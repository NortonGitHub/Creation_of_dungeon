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
    auto beforeAnimation = _animation;
    if (beforeAnimation != nullptr)
        beforeAnimation->GetGraphPtr()->SetDisplayMode(false);

    _animation = _animations[animationName];
    if (_animation != nullptr)
        _animation->GetGraphPtr()->SetDisplayMode(true);

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

    Switch(animationName);
}

void Animator::AddAnimation(std::string name, std::shared_ptr<GraphArray> animation)
{
    bool isFirstAdd = (_animations.size() == 0);
    _animations.insert(std::make_pair(name, animation));

    if (animation != nullptr)
        animation->GetGraphPtr()->SetDisplayMode(false);

    if (isFirstAdd)
        Switch(name);
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
    if (_animation == nullptr)
        return;

    _animation->Update();
}

/*
void Animator::Draw(const Vector2D vec, bool flip)
{
    _animation->_graphPtr->Draw(vec, flip);
}
*/