#include "Goal.h"
#include "TiledVector.h"
#include "TileField.h"
#include "Character.h"
#include "ColleagueNotifyer.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

Goal::Goal(TiledVector tilePos, ColleagueNotifyer& notifyer, MessageReciever& reciever, int permitivePassedNum)
: TiledObject(tilePos)
, _passedNum(0)
, _permitivePassedNum(permitivePassedNum)
, _notifyer(notifyer)
, _reciever(reciever)
{
    _type = TiledObject::Type::GOAL;
    _tdb = _reciever._processer.CreateTalkData("csv/talkData/missed.csv", Talk_Type::nomal);
}

Goal::Goal(TiledVector tilePos, ColleagueNotifyer& notifyer)
    : TiledObject(tilePos)
    , _passedNum(0)
    , _permitivePassedNum(99)
    , _notifyer(notifyer)
    , _reciever(MessageReciever())
{
    _type = TiledObject::Type::GOAL;
}


Goal::~Goal()
{
    FIELD->RemoveObject(*this);
}


void Goal::Init()
{
    auto tilePos = GetTilePos();
    auto fieldType = GetTile().lock()->GetFieldType();
    std::string fileName = GetMapChipGraphDirectory(fieldType);

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


void Goal::Update()
{
}


void Goal::Draw()
{
    _position = GetTilePos().GetWorldPos();
    GraphicalObject::Draw();
}


void Goal::Interact(Character &chara)
{
    //敵のみ通過したとカウントする
    if (chara.GetType() == Type::ENEMY)
    {
        //通過したキャラは諦めるように通知する
        _notifyer.NotifyRemoveTarget(chara);
        _passedNum++;

        if (_passedNum == _permitivePassedNum)
            _reciever.Recieve(_tdb);
    }
}


bool Goal::IsOverwritable(TiledObject* overwriter)
{
    //MEMO : ロード時にブロックが上に被らないようにしている
    if(overwriter->GetType() == Type::BLOCK)
        return false;

    if (overwriter->GetType() == Type::MONSTER)
        return false;

    return true;
}