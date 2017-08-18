#pragma once
#include "TiledObject.h"
#include "../Sound/Sound.h"

class GraphArray;

class Trap : public TiledObject
{
public:
    Trap(TiledVector startPos, int duravity, int level);
    ~Trap();

    virtual void Update() override;
    virtual void Draw() override;

    bool IsBrakeable(int brokerLevel) const { return _level <= brokerLevel; };

    //能動動作できるオブジェクトから呼び出される関数
    virtual void Interact(Character& character) override {};

    //そのオブジェクトの上に別のオブジェクトが乗れるかどうか
    //overwriter : 上に乗ろうとするオブジェクト
    virtual bool IsOverwritable(TiledObject* overwriter) override { return true; };

    //アイテム取得での消失や召喚されたかどうかなど、
    //オブジェクトは生成しても判定に用いるかどうかを判断するのに用いる.
    virtual bool IsEnable() const { return (_cost <= _duravity); }

    //トラップを起動できるかどうか
    virtual bool IsActivatable() const;

    //トラップを起動
    virtual void Activate();

    static void CreateTrap(std::string typeName, int countX, int countY, std::vector<std::shared_ptr<TiledObject>>& objects);

protected:

    static bool Contained(const GraphArray& animation, const Vector2D& pos);

    //耐久力
    int _duravity;

    //発動時に消耗する量
    int _cost;

    //破壊可能かを示す値
    int _level;

    Sound _activateSound;
};

