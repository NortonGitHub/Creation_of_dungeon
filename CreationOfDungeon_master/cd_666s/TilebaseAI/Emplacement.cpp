#include "Emplacement.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "MagicBall.h"


#include "../InputManager/MouseInput.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"


Emplacement::Emplacement(TiledVector pos, int cost, int power, int attack, TiledVector::Direction direction)
    : Trap(pos, cost, 5)
    , _power(power)
    , _attack(attack)
    , _shootDirection(direction)
{
    _graph.Load("resourse/graph/trap/bow.png");
    _bulletImage = IMAGE_RESOURCE_TABLE->Create("resourse/graph/tiledObject/magicBall_B.png");

    _directedGraph.Set(&_graph, 32, 32, 4, 1);
    _directedGraph._isPlaying = false;

    switch (_shootDirection)
    {
    case TiledVector::Direction::LEFT:
        _directedGraph.SetIndex(0);
        break;

    case TiledVector::Direction::RIGHT:
        _directedGraph.SetIndex(2);
        break;

    case TiledVector::Direction::FORWARD:
        _directedGraph.SetIndex(3);
        break;


    case TiledVector::Direction::BACK:
        _directedGraph.SetIndex(1);
        break;
    }
}


Emplacement::~Emplacement()
{
}


void Emplacement::Activate()
{
    Trap::Activate();

    //ŽË’ö•ûŒü‚©‚ç’²‚×‚é”ÍˆÍ‚ðŒˆ’è
    auto fieldSize = FIELD->GetFieldSize();
    TiledVector move;
    int distance = 0;
    switch (_shootDirection)
    {
    case TiledVector::Direction::LEFT:
        distance = fieldSize._x;
        move = TiledVector::left;
        break;

    case TiledVector::Direction::RIGHT:
        distance = fieldSize._x;
        move = TiledVector::right;
        break;

    case TiledVector::Direction::FORWARD:
        distance = fieldSize._y;
        move = TiledVector::up;
        break;


    case TiledVector::Direction::BACK:
        distance = fieldSize._y;
        move = TiledVector::down;
        break;
    }

    TiledVector tilePos = GetTilePos();
    OBJECT_MGR->Add(std::make_shared<MagicBall>(_power, _attack, distance, 10, tilePos, _shootDirection, TiledObject::Type::MONSTER, _bulletImage, true));
}


bool Emplacement::IsActivatable() const
{
    if (!Trap::IsActivatable())
        return false;

    if (!MOUSE->DoubleClicked())
        return false;

    return (Contain(MOUSE->GetCursorPos()));
}
