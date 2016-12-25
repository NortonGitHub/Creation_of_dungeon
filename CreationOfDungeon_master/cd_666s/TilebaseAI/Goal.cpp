#include "Goal.h"
#include "TiledVector.h"
#include "TileField.h"
#include "Character.h"
#include "ColleagueNotifyer.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

Goal::Goal(TiledVector tilePos, ColleagueNotifyer& notifyer)
: TiledObject(tilePos)
, _passedNum(0)
, _notifyer(notifyer)
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
    }
}


bool Goal::IsOverwritable(TiledObject* overwriter)
{
    //MEMO : ロード時にブロックが上に被らないようにしている
    if(overwriter->GetType() == Type::BLOCK)
        return false;
    
    return true;
}