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

    //�}�b�v�`�b�v�̗�̔ԍ���Ԃ�
    int GetColumn() const { return x; }
    //�}�b�v�`�b�v�̍s�̔ԍ���Ԃ�
    int GetRow() const { return y; }
    //�}�b�v�`�b�v�̎�ނ������ԍ���Ԃ�
    int GetMapChipNum() const { return map_chip_num; }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    //�}�b�v�`�b�v�̉�ʏ�ł̍��[���W��Ԃ�
    int GetLeftPos() const { return x*width; }
    //�}�b�v�`�b�v�̉�ʏ�ł̏�[���W��Ԃ�
    int GetTopPos() const { return y*height; }
    //�}�b�v�`�b�v�̉�ʏ�ł̉E�[���W��Ԃ�
    int GetRightPos() const { return (x*width) + width; }
    //�}�b�v�`�b�v�̉�ʏ�ł̉��[���W��Ԃ�
    int GetBottomPos() const { return (y*height) + height; }

    void ChangingScale(double _per) {
        width *= _per;
        height *= _per;
    }


private:
    const int fixed_width;
    const int fixed_height;

    int x;  //�����}�X�ڂ��������t�B�[���h
    int y;  //�c���}�X�ڂ��������t�B�[���h

    int width;
    int height;

    int map_chip_num;
};