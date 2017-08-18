#pragma once
#include "BattleParameter.h"
#include "ParameterEffecter.h"

class ParameterMultiplier : public ParameterEffecter
{
public:

    //百分率で指定
    ParameterMultiplier(BattleParameter multiplyPercent, int count, bool isPositive);
    ~ParameterMultiplier();

    //対象に効果を付与
    void AffectParameter(BattleParameter& param) override;

    // MEMO : バフの表現方法が決まるまでのデバッグ表示
    void DrawEffecter(Vector2D anchorPos) override;

private:

    BattleParameter _multiplyPercent;
};

