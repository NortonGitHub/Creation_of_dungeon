#pragma once
#include <string>
#include <vector>
#include "MapData.h"
#include "UIContent.h"
#include "CharaBase.h"
class CSVDataLoader
{
public:
	CSVDataLoader();
	~CSVDataLoader();

	static void LoadMapCSV(std::vector<MapData> &map_data, int stagenum);

	static void LoadUICSV(std::vector<UIContent> &ui_data, std::string scene_name);

	static void LoadCharaCSV(std::vector<CharaBase*> &chara_data, std::string stage_name);
};

