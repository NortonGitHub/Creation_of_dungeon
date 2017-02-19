#pragma once
#include "BattleParameter.h"
#include "ParameterEffecter.h"

class ParameterRiser : public ParameterEffecter
{
public:
    //加算される値を指定
    ParameterRiser(BattleParameter addedParameter, int count, bool isPositive);
    ~ParameterRiser();

    //対象に効果を付与
    void AffectParameter(BattleParameter& param) override;

    // MEMO : バフの表現方法が決まるまでのデバッグ表示
    void DrawEffecter(Vector2D anchorPos) override;

private:

    BattleParameter _addedParameter;
};

