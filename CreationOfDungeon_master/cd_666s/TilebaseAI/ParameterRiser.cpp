#include "ParameterRiser.h"
#include "../DebugDraw.h"

ParameterRiser::ParameterRiser(BattleParameter addedParameter, int count, bool isPositive)
    : ParameterEffecter(count, isPositive)
    , _addedParameter(std::move(addedParameter))
{
}


ParameterRiser::~ParameterRiser()
{
}


//対象に効果を付与
void ParameterRiser::AffectParameter(BattleParameter& param)
{
    param += _addedParameter;
}


// MEMO : バフの表現方法が決まるまでのデバッグ表示
void ParameterRiser::DrawEffecter(Vector2D anchorPos)
{
    Debug::DrawCircle(anchorPos, 16, ColorPalette::BLACK4, false);
    if (IsPositive())
        Debug::DrawString(anchorPos - Vector2D(8, 8), "P+");
    else
        Debug::DrawString(anchorPos - Vector2D(8, 8), "P-");
}