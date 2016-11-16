#include "DxLib.h"
#include "MapProcessManager.h"
#include "MouseManager.h"



MapProcessManager::MapProcessManager()
{
	staticMap.reserve(100);
	dynamicMap.reserve(100);
	
}

MapProcessManager::MapProcessManager(std::string stage_num) {

	staticMap.reserve(100);
	dynamicMap.reserve(100);

	std::shared_ptr<MapBase> _map = std::make_shared<MapBase>(MapBase());

	//MapProcessManager();

	int num = atoi(stage_num.c_str());

	if (num == 0) {
		printf("�G���[����:�X�e�[�W��ǂݍ��ނ��Ƃ��ł��Ȃ�����");
		exit(0);
	}

	_map->LoadMapData(num);

	_map->GetStaticMap(staticMap);
	_map->GetDynamicMap(dynamicMap);

}


MapProcessManager::~MapProcessManager()
{
	staticMap.shrink_to_fit();
	dynamicMap.shrink_to_fit();
}

void MapProcessManager::Update(MouseContent mc)
{
	for (auto itr : staticMap) {
		Vector2D pos1(itr->GetLeftPos(), itr->GetTopPos());		//���[,��[
		Vector2D pos2(itr->GetRightPos(), itr->GetBottomPos());	//�E�[,���[

		if (MouseManager::OnMouseOver(mc, pos1, pos2)) {
			if (mc._mouse_left_click) {
				/*�����Ƀ}�b�v�`�b�v���N���b�N�����Ƃ��̏������L��*/
			}
		}
	}
}

void MapProcessManager::Draw()
{
	for (auto itr : staticMap) {
		int _x = itr->GetLeftPos();
		int _y = itr->GetTopPos();
		int _num = itr->GetMapChipNum();

		DrawGraph(_x, _y, _num, TRUE);
	}

	for (auto itr : dynamicMap) {
		int _x = itr->GetLeftPos();
		int _y = itr->GetTopPos();
		int _num = itr->GetMapChipNum();

		DrawGraph(_x, _y, _num, TRUE);
	}
}
