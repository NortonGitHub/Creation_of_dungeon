#include "Emplacement.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "ShottenObject.h"


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

    std::string arrowString = "resourse/graph/trap/arrow_";
    switch (_shootDirection)
    {
    case TiledVector::Direction::BACK:
        arrowString += "up.png";
        break;

    case TiledVector::Direction::FORWARD:
        arrowString += "down.png";
        break;

    case TiledVector::Direction::LEFT:
        arrowString += "left.png";
        break;

    case TiledVector::Direction::RIGHT:
        arrowString += "right.png";
        break;
    default:
        break;
    }
    _bulletImage = IMAGE_RESOURCE_TABLE->Create(arrowString);

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
    OBJECT_MGR->Add(std::make_shared<ShottenObject>(_power, _attack, distance, 10, tilePos, _shootDirection, TiledObject::Type::MONSTER, _bulletImage, true));
}


bool Emplacement::IsActivatable() const
{
    if (!Trap::IsActivatable())
        return false;

    if (!MOUSE->DoubleClicked())
        return false;

    return (Trap::Contained(_directedGraph, MOUSE->GetCursorPos()));
}


bool Emplacement::Contain(Vector2D pos) const
{
    auto size = _directedGraph.GetSingleSize();

    if (pos._x < _position._x)
        return false;
    if (pos._y < _position._y)
        return false;
    if (_position._x + size._x * TILE_SCALE < pos._x)
        return false;
    if (_position._y + size._y * TILE_SCALE  < pos._y)
        return false;

    return true;
}
