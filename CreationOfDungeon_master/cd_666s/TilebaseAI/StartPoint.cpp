#include "StartPoint.h"
#include "TiledVector.h"
#include "TileField.h"
#include "Enemy.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

StartPoint::StartPoint(TiledVector tilePos)
: TiledObject(tilePos)
, _frameFromStart(0)
{
    _type = TiledObject::Type::START;
}


StartPoint::~StartPoint()
{
    FIELD->RemoveObject(*this);
}


void StartPoint::Init()
{
    auto tilePos = GetTilePos();
    std::string fileName = RESOURCE_TABLE->GetFolderPath() + "graph/background/";

    if (!FIELD->IsInside(tilePos + TiledVector(0, -1)))
    {
        fileName += "hole_f";
    }
    else if (!FIELD->IsInside(tilePos + TiledVector(0, 1)))
    {
         fileName += "hole_b";
    }

    _graph.Load(fileName + ".png");
    _graph.SetPosition(tilePos.GetWorldPos());
    _graph.GetTexturePtr()->SetPriority(-1);
}


void StartPoint::AddToAppearList(Enemy* enemy, long appearFrame)
{
    _appearData.push_back(std::make_pair(enemy, appearFrame));
}


void StartPoint::Update()
{
    for (size_t i=0; i<_appearData.size(); ++i)
    {
        if (_appearData[i].second == _frameFromStart)
        {
            _appearData[i].first->Appear();
        }
    }
    
    _frameFromStart++;
}


void StartPoint::Draw()
{
}


bool StartPoint::IsOverwritable(TiledObject* overwriter)
{
    //MEMO : ロード時にブロックが上に被らないようにしている
    if(overwriter->GetType() == Type::BLOCK)
        return false;
        
    return true;
}