#include "River.h"
#include "TileField.h"
#include "../Resources//ResourceManager.h"
#include "../DebugDraw.h"

River::River(TiledVector tilePos)
    : Obstacle(tilePos)
{
	typeText = "";
}

River::River(TiledVector tilePos, std::string typeText)
	: Obstacle(tilePos) 
{
	_type = TiledObject::Type::DEFAULT;
	this->typeText = typeText;

}

River::~River()
{
}


void River::Init()
{
    auto tilePos = GetTilePos();
    auto fieldType = GetTile().lock()->GetFieldType();
    std::string fileName = GetMapChipGraphDirectory(fieldType);

	if (typeText.empty() || typeText.find("$") == std::string::npos) {
		//¶‚ªì‚È‚ç
		if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
		{
			//ã‚ªì‚È‚ç
			if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
				fileName += "river_corner_lr";
			//‰º‚ªì‚È‚ç
			else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
				fileName += "river_corner_ur";
			else
				fileName += "river_h";
		}
		//‰E‚ªì‚È‚ç
		else if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
		{
			//ã‚ªì‚È‚ç
			if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
				fileName += "river_corner_ll";
			//‰º‚ªì‚È‚ç
			else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
				fileName += "river_corner_ul";
			else
				fileName += "river_h";
		}
		//‰º‚ªì‚È‚ç
		else if (FIELD->GetRawNumber(tilePos + TiledVector(0, 1)) == 6)
		{
			//‰E‚ªì‚È‚ç
			if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
				fileName += "river_corner_ll";
			//¶‚ªì‚È‚ç
			else if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
				fileName += "river_corner_lr";
			else
				fileName += "river_v";
		}
		//ã‚ªì‚È‚ç
		else if (FIELD->GetRawNumber(tilePos + TiledVector(0, -1)) == 6)
		{
			//‰E‚ªì‚È‚ç
			if (FIELD->GetRawNumber(tilePos + TiledVector(1, 0)) == 6)
				fileName += "river_corner_ul";
			//¶‚ªì‚È‚ç
			else if (FIELD->GetRawNumber(tilePos + TiledVector(-1, 0)) == 6)
				fileName += "river_corner_ur";
			else
				fileName += "river_v";
		}
		else
		{
			fileName += "river_v";
		}

	}
	else {

		std::vector<std::string> temp;

		temp.clear();

		temp.push_back("lr");
		temp.push_back("ur");
		temp.push_back("ll");
		temp.push_back("ul");
		temp.push_back("v");
		temp.push_back("h");

		for (std::string str : temp) {
			if (typeText.find(str) != std::string::npos) {
				if (str.size() == 1) {
					fileName += "river_" + str;
				}
				else {
					fileName += "river_corner_" + str;
				}
			}
		}

	}

    _graph.Load(fileName + ".png");
    _graph.SetPosition(tilePos.GetWorldPos());
    TiledObject::Init();
}


bool River::IsOverwritable(TiledObject* overwriter) {

	if (overwriter->GetType() == TiledObject::Type::ATTACK) {
		return true;
	}

	return false;

}

