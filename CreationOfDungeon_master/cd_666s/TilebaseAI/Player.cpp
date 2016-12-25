#include "Player.h"
#include "../InputManager/InputManager.h"
#include "../Resources/ResourceManager.h"
#include "TileField.h"
#include "AI/Breadcrumb.h"

Player::Player(TiledVector pos, ColleagueNotifyer& notifyer)
    : Character(pos, {10000, 30, 30, 100}, notifyer)
    , _time(0)
    , _updateInterval(15)
{
    _graph.Load(RESOURCE_TABLE->GetFolderPath() + "graph/player.png");

    _position = pos.GetWorldPos();
    _beforeTilePos = GetTilePos();
    _type = TiledObject::Type::MONSTER;
}


Player::~Player()
{
}


void Player::MoveToNext(TiledVector offset)
{
    //直前の位置に足跡生成
    TiledVector tilePos = GetTilePos();
    FIELD->RegistBreadcrumb(new Breadcrumb(_beforeTilePos, 60), _beforeTilePos);

    //移動
    tilePos += offset;
    FIELD->MoveObject(*this, tilePos);
    _time = 0;
}


void Player::Update()
{
    Character::CheckClicked();
    
    _time++;

    if (_time < _updateInterval)
        return;

    //プレイアブルなキャラクターなのでAIは必要なし
    //Think();
    Act();
}


void Player::Think()
{
}


void Player::Act()
{
    TiledVector tilePos = GetTilePos();
    _beforeTilePos = tilePos;
        
    if (KEYBOARD->ButtonBeingPressed(KeyInput::KeyType::KEY_ARROW_LEFT))
        MoveToNext(TiledVector(-1, 0));
    else if (KEYBOARD->ButtonBeingPressed(KeyInput::KeyType::KEY_ARROW_RIGHT))
        MoveToNext(TiledVector(1, 0));
    
    if (KEYBOARD->ButtonBeingPressed(KeyInput::KeyType::KEY_ARROW_DOWN))
        MoveToNext(TiledVector(0, -1));
    else if (KEYBOARD->ButtonBeingPressed(KeyInput::KeyType::KEY_ARROW_UP))
        MoveToNext(TiledVector(0, 1));
}


void Player::Draw()
{
    auto vec = (GetTilePos() - _beforeTilePos).GetWorldPos();
    _position += vec * (1.0 / _updateInterval);
    GraphicalObject::Draw();
}


bool Player::IsOverwritable(TiledObject* overwriter)
{
    return false;
}