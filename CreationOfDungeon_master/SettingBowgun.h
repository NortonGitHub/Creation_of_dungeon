#pragma once
#include "cd_666s\TilebaseAI\TiledObject.h"
class SettingBowgun :
    public TiledObject
{
public:
    SettingBowgun(TiledVector tilePos);
    ~SettingBowgun();

    void Init();

    //能動動作できるオブジェクトから呼び出される関数
    void Interact(Character& character);

    //そのオブジェクトの上に別のオブジェクトが乗れるかどうか
    //overwriter : 上に乗ろうとするオブジェクト
    bool IsOverwritable(TiledObject* overwriter);

    void OnClicked();

    void Update() override;
    void Draw() override;

private:
    std::string _name;
};

