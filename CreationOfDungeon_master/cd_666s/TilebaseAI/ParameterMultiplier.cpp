#include "ParameterMultiplier.h"
#include "../DebugDraw.h"

ParameterMultiplier::ParameterMultiplier(BattleParameter multiplyPercent, int count, bool isPositive)
    : ParameterEffecter(count, isPositive)
    , _multiplyPercent(std::move(multiplyPercent))
{
}


ParameterMultiplier::~ParameterMultiplier()
{
}


//対象に効果を付与
void ParameterMultiplier::AffectParameter(BattleParameter& param)
{
    if (_multiplyPercent._maxHP != 0)
        param._maxHP *= (_multiplyPercent._maxHP / 100.0);
    if (_multiplyPercent._hp != 0)
        param._hp *= (_multiplyPercent._hp / 100.0);

    if (_multiplyPercent._attack != 0)
        param._attack *= (_multiplyPercent._attack / 100.0);
    if (_multiplyPercent._defence != 0)

        param._defence *= (_multiplyPercent._defence / 100.0);
    if (_multiplyPercent._magicAttack != 0)
        param._magicAttack *= (_multiplyPercent._magicAttack / 100.0);
    if (_multiplyPercent._magicDefence != 0)
        param._magicDefence *= (_multiplyPercent._magicDefence / 100.0);

    if (_multiplyPercent._speed != 0)
        param._speed *= (_multiplyPercent._speed / 100.0);
}


// MEMO : バフの表現方法が決まるまでのデバッグ表示
void ParameterMultiplier::DrawEffecter(Vector2D anchorPos)
{
    Debug::DrawCircle(anchorPos, 16, ColorPalette::BLACK4, false);
    if (IsPositive())
        Debug::DrawString(anchorPos - Vector2D(8, 8), "P↑");
    else
        Debug::DrawString(anchorPos - Vector2D(8, 8), "P↓");
}