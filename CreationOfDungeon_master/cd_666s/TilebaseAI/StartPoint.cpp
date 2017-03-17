#include "StartPoint.h"
#include "TiledVector.h"
#include "TileField.h"
#include "Enemy.h"
#include "MessageReciever.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

StartPoint::StartPoint(TiledVector tilePos, MessageReciever& reciever)
: TiledObject(tilePos)
, _frameFromStart(0)
, _currentIndex(0)
, _reciever(reciever)
{
    _type = TiledObject::Type::START;

    _intrudeMessage = _reciever._processer.CreateTalkData("csv/talkData/blaver_intruding.csv", Talk_Type::dynamic);
}


StartPoint::~StartPoint()
{
    FIELD->RemoveObject(*this);
}


void StartPoint::Init()
{
    auto tilePos = GetTilePos();
    std::string fileName = "resourse/graph/background/";

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
    _graph.SetPriority(Sprite::Priority::FIELD_OBJECT);

    TiledObject::Init();
}


void StartPoint::AddToAppearList(std::weak_ptr<Enemy> enemy, long appearFrame)
{
    _appearData.push_back(std::make_pair(enemy, appearFrame));
}


void StartPoint::Update()
{
    for (size_t i=0; i<_appearData.size(); ++i)
    {
        if (_appearData[i].first.expired())
            continue;

        //到達時間に達した敵から追加
        if (_appearData[i].second == _frameFromStart)
        {
            _appearData[i].first.lock()->Appear();
            _currentIndex++;

            //_reciever.Recieve(_intrudeMessage);
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
        
    if (overwriter->GetType() == Type::MONSTER)
        return false;

    return true;
}

//次の敵が出現するまで
int StartPoint::GetTimeUnitlNext() const
{
    if (_appearData.size() <= _currentIndex)
        return NobodyIntruder();

    return _appearData[_currentIndex].second - _frameFromStart;
}


Character* StartPoint::GetNextEnemy()
{
    if (_appearData.size() <= _currentIndex)
        return nullptr;

    if (_appearData[_currentIndex].first.expired())
        return nullptr;

    return _appearData[_currentIndex].first.lock().get();
}