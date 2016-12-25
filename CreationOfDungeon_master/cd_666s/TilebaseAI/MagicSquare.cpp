#include "MagicSquare.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "Monster.h"
#include "../InputManager/InputManager.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

MagicSquare::MagicSquare(TiledVector tilePos, Monster& monster)
: TiledObject(tilePos)
, _monster(monster)
{
    _type = TiledObject::Type::MAGIC_SQUARE;
    _position = GetTilePos().GetWorldPos();

    _graph.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/magicSquare_none.png");
    _graph_ready.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/magicSquare_ready.png");
    _graph.SetPosition(_position);
    _graph_ready.SetPosition(_position);

    _graph.GetTexturePtr()->SetPriority(-1);
    _graph_ready.GetTexturePtr()->SetPriority(-1);
}


MagicSquare::~MagicSquare()
{
}


void MagicSquare::Update()
{
    if (MOUSE->DoubleClicked())
    {
        auto tiledCursorPos = TiledVector::ConvertToTiledPos(MOUSE->GetCursorPos());
        if (!FIELD->IsInside(tiledCursorPos))
            return;
        
        //自分の位置がクリックされていなければ終了
        if (tiledCursorPos != GetTilePos())
            return;
        
        //生きていたら
        if (_monster.IsAlive() && _monster.IsEnable())
        {
            //送還
            WarpHomeMonster();
            return;
        }
        //召喚
        ProduceMonster();
    }
}


void MagicSquare::WarpHomeMonster()
{
    //上に何かあるなどでモンスターを移動できないとワープできない
    if (!GetTile()->IsRegistable(_monster))
        return;
        
    _monster.WarpToHome(*this);
}


void MagicSquare::ProduceMonster()
{
    //上に何かあるなどでモンスターを移動できないと召喚できない
    if (!GetTile()->IsRegistable(_monster))
        return;
    
    if (_monster.IsReadyToProduce())
        _monster.Appear();
}


void MagicSquare::Draw()
{
    if (_monster.IsReadyToProduce())
    {
        _graph_ready.SetDisplayMode(true);
        _graph.SetDisplayMode(false);
    }
    else
    {
        _graph_ready.SetDisplayMode(false);
        _graph.SetDisplayMode(true);
    }
}


bool MagicSquare::IsOverwritable(TiledObject* overwriter)
{
    return true;
}


void MagicSquare::Interact(Character& character)
{
    auto hp = character._battleParameter._hp;
    if (hp < character._maxHP)
    {
        hp += 1;
        hp = max(0, min(hp, character._maxHP));
        character._battleParameter._hp = hp;
    }
}
