#pragma once

class MapData {
public:
    MapData(int _x, int _y, int chip_num)
        :fixed_width(32),
        fixed_height(32)
    {
        map_chip_num = chip_num;
        x = _x;
        y = _y;

        width = fixed_width;
        height = fixed_height;
    };

    //マップチップの列の番号を返す
    int GetColumn() const { return x; }
    //マップチップの行の番号を返す
    int GetRow() const { return y; }
    //マップチップの種類を示す番号を返す
    int GetMapChipNum() const { return map_chip_num; }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    //マップチップの画面上での左端座標を返す
    int GetLeftPos() const { return x*width; }
    //マップチップの画面上での上端座標を返す
    int GetTopPos() const { return y*height; }
    //マップチップの画面上での右端座標を返す
    int GetRightPos() const { return (x*width) + width; }
    //マップチップの画面上での下端座標を返す
    int GetBottomPos() const { return (y*height) + height; }

    void ChangingScale(double _per) {
        width *= _per;
        height *= _per;
    }


private:
    const int fixed_width;
    const int fixed_height;

    int x;  //横何マス目かを示すフィールド
    int y;  //縦何マス目かを示すフィールド

    int width;
    int height;

    int map_chip_num;
};