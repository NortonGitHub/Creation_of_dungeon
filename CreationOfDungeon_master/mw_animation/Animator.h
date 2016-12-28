#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <unordered_map>
#include <memory>

#include "GraphArray.h"

/*
������GraphArray�N���X�ɗL�ӂȖ��O������
�؂�ւ��\���ł���悤�ɂ���
GraphArray�̊g�����W���[��
*/

class Animator
{
public:
    Animator();
    ~Animator();

    //�Đ�����A�j���\�V�����؂�ւ�
    void Switch(std::string animationName);
    //�A�j����؂�ւ��A���O�̃A�j�����ŏ��̏�Ԃ�
    void SwitchWithReset(std::string animationName);

    //�A�j���[�V�����ɗL�ӂȖ��O��t���Ēǉ�����
    void AddAnimation(std::string, std::shared_ptr<GraphArray>);

    //�w��̂Ȃ܂��̃A�j���[�V�������폜����
    void RemoveAnimation(std::string animationName);

    void Update();
    //void Draw(const Vector2D vec, bool flip);

    std::string GetCurrentAnimationName(){ return _currentName; }
    Sprite* GetCurrentGraph() { return _animation->_graphPtr; }
    std::shared_ptr<GraphArray> GetCurrentAnimation() { return _animation; }

private:

    //�o�^���ꂽ�A�j���[�V�����ꗗ
    std::unordered_map<std::string, std::shared_ptr<GraphArray>> _animations;

    //���݂̃A�j���[�V����
    std::shared_ptr<GraphArray> _animation;

    std::string _currentName;
};

#endif