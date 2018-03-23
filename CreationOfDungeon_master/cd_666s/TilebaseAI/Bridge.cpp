#include "Bridge.h"
#include "TiledVector.h"
#include "TileField.h"
#include "../Resources//ResourceManager.h"
#include "../DebugDraw.h"


Bridge::Bridge(std::string typeName, TiledVector tilePos)
	: TiledObject(tilePos)
{
	_type = TiledObject::Type::DEFAULT;
	this->typeName = typeName;
}


Bridge::~Bridge()
{
}


void Bridge::Init()
{
	auto tilePos = GetTilePos();
	auto fieldType = GetTile().lock()->GetFieldType();
	std::string fileName = GetMapChipGraphDirectory(fieldType);
	fileName += GetNameFromTypeName();

	
	_graph.Load(fileName + ".png");
	
	
	_graph.SetPosition(tilePos.GetWorldPos());
	TiledObject::Init();
}

void Bridge::Update()
{
}


void Bridge::Draw()
{
}


bool Bridge::IsOverwritable(TiledObject* overwriter)
{

	return true;
}



std::string Bridge::GetNameFromTypeName() {

	if (typeName.find("$") == std::string::npos) {
		return "bridge_h";
	}

	if (typeName.find("h") != std::string::npos) {
		return "bridge_h";
	}

	if (typeName.find("v") != std::string::npos) {
		return "bridge_v";
	}

	return "bridge_h";

}









