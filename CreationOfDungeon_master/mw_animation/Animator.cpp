#include "Animator.h"


Animator::Animator()
{
}


Animator::~Animator()
{
}

//�Đ�����A�j���\�V�����؂�ւ�
void Animator::Switch(std::string animationName)
{
    _animation = _animations[animationName];
    _currentName = animationName;
}

//�A�j����؂�ւ��A���O�̃A�j�����ŏ��̏�Ԃ�
void Animator::SwitchWithReset(std::string animationName)
{
    auto temp = _animation;

    //���d�Đ��h�~
    if (temp == _animations[animationName])
        return;
    else
    {
        //���O�̃A�j���[�V�������X�^�[�g�ʒu��
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

    //�w��̃A�j����������ΏI��
    if (removeAnimation == nullptr)
        return;

    //���ݍĐ����̃A�j���[�V�����Ɠ������ƁA�I��
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