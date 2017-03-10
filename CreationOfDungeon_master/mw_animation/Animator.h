#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <functional>
#include <unordered_map>
#include <memory>

#include "GraphArray.h"

/*
複数のGraphArrayクラスに有意な名前をつけて
切り替え表示できるようにする
GraphArrayの拡張モジュール
*/

class Animator
{
public:
    Animator();
    ~Animator();

    //再生するアニメ―ション切り替え
    void Switch(std::string animationName);
    //アニメを切り替え、直前のアニメを最初の状態へ
    void SwitchWithReset(std::string animationName);

    //アニメーションに有意な名前を付けて追加する
    void AddAnimation(std::string, std::shared_ptr<GraphArray>);

    //指定のなまえのアニメーションを削除する
    void RemoveAnimation(std::string animationName);

    void Update();
    //void Draw(const Vector2D vec, bool flip);

    void Transform(std::function<void(GraphArray*)> func)
    {
        for (auto animation : _animations)
        {
            if (animation.second != nullptr)
                func(animation.second.get());
        }
    }

    std::string GetCurrentAnimationName() const { return _currentName; }
    Sprite* GetCurrentGraph() const { return _animation->_graphPtr; }
    std::shared_ptr<GraphArray> GetCurrentAnimation() const { return _animation; }

private:

    //登録されたアニメーション一覧
    std::unordered_map<std::string, std::shared_ptr<GraphArray>> _animations;

    //現在のアニメーション
    std::shared_ptr<GraphArray> _animation;

    std::string _currentName;
};

#endif