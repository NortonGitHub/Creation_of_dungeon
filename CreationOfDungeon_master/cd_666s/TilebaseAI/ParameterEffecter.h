#pragma once
#include "../../Vector2D.h"

class BattleParameter;

class ParameterEffecter
{
public:
    ParameterEffecter(int continuousTime, bool isPositive);
    ~ParameterEffecter();

    //時間経過
    void UpdateCounter();

    //追加効果が有効かどうか
    bool IsEnable() const { return _time < _affectionTime; }

    bool IsPositive() const { return _isPositive; }

    //対象に効果を付与
    virtual void AffectParameter(BattleParameter& param) = 0 {};

    // MEMO : バフの表現方法が決まるまでのデバッグ表示
    virtual void DrawEffecter(Vector2D anchorPos) = 0 {};

private:

    int _time;
    int _affectionTime;

    //バフかデバフか
    bool _isPositive;

    //効果を表すアイコン
    //Sprite _icon;
};

