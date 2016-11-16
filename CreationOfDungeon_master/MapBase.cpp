#include "MapBase.h"
#include "CSVDataLoader.h"


MapBase::MapBase()
{
	staticMap.reserve(100);
	dynamicMap.reserve(100);
}


MapBase::~MapBase()
{
	staticMap.shrink_to_fit();	//	std::vector<MapData*>().swap(staticMap) ‚Æ“¯‹`
	dynamicMap.shrink_to_fit();
}

void MapBase::LoadMapData(int _stage_num)
{
	std::vector<MapData> temp;
	CSVDataLoader::LoadMapCSV(temp ,_stage_num);

	for (auto it :temp) {
		staticMap.push_back(std::make_shared<MapData>(it));
	}
}


