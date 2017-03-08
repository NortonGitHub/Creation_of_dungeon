#pragma once
#include "TiledObject.h"

class Trap : public TiledObject
{
public:
    Trap(TiledVector startPos, int duravity, int level);
    ~Trap();

    virtual void Update() override;

    bool IsBrakeable(int brokerLevel) const { return _level <= brokerLevel; };

    //能動動作できるオブジェクトから呼び出される関数
    virtual void Interact(Character& character) override {};

    //そのオブジェクトの上に別のオブジェクトが乗れるかどうか
    //overwriter : 上に乗ろうとするオブジェクト
    virtual bool IsOverwritable(TiledObject* overwriter) override { return true; };

    //アイテム取得での消失や召喚されたかどうかなど、
    //オブジェクトは生成しても判定に用いるかどうかを判断するのに用いる.
    virtual bool IsEnable() const { return true; }

protected:

    //耐久力
    int _duravity;

    //発動時に消耗する量
    int _cost;

    //破壊可能かを示す値
    int _level;
};

