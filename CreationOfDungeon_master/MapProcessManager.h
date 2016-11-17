#pragma once
#include <memory>
#include <vector>
#include "MapBase.h"
#include "MouseContent.h"


class MapProcessManager
{
public:
    MapProcessManager();
    MapProcessManager(std::string stage_num);
    ~MapProcessManager();

    void Update(MouseContent mc);
    void Draw();

private:

    std::vector<std::shared_ptr<MapData>> staticMap;    //���n�ƂȂ�}�b�v�f�[�^
    std::vector<std::shared_ptr<MapData>> dynamicMap;   //�I�u�W�F�N�g�ݒu�̍ۂɍ��W������������}�b�v�f�[�^
};

