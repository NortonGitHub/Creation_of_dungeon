#pragma once
#include "MapData.h"
#include <vector>
#include <memory>

class MapBase
{
public:
    MapBase();
    ~MapBase();

    void LoadMapData(int _stage_num);

    void GetStaticMap(std::vector<std::shared_ptr<MapData>>& _static) {
        _static = std::move(staticMap); staticMap.at(0);
    }

    void GetDynamicMap(std::vector<std::shared_ptr<MapData>>& _dynamic) {
        _dynamic = std::move(dynamicMap);
    }

private:
    /*
    staticMap�̏��dynamicMap���d�ˍ��킹��l�ɏ������тɕ`����s��
    */
    std::vector<std::shared_ptr<MapData>> staticMap;    //���n�ƂȂ�}�b�v�f�[�^
    std::vector<std::shared_ptr<MapData>> dynamicMap;   //�I�u�W�F�N�g�ݒu�̍ۂɍ��W������������}�b�v�f�[�^

    //std::vector<MapData*> staticMap;  //���n�ƂȂ�}�b�v�f�[�^
    //std::vector<MapData*> dynamicMap; //�I�u�W�F�N�g�ݒu�̍ۂɍ��W������������}�b�v�f�[�^

};

