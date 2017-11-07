#include "MonsterController.h"
#include "BattlingTile.h"
#include "Monster.h"
#include "MagicSquare.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../DebugDraw.h"
#include "../InputManager/InputManager.h"

MonsterController::MonsterController()
    : _monster(nullptr)
{
}


MonsterController::~MonsterController()
{
}


void MonsterController::Init()
{
    _monster = nullptr;
}


void MonsterController::Update()
{
    if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) {
        //return;

        //クリック位置がフィールド内かチェック
        auto cursorPos = MOUSE->GetCursorPos();
        auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);
        if (FIELD->IsInside(tiledCursorPos)) {
            //return;

            if (_monster == nullptr)
                SelectMonster(cursorPos);
            else
                ControlMonster(cursorPos);
        }
    }

    if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_R)) {

        //クリック位置がフィールド内かチェック
        auto cursorPos = MOUSE->GetCursorPos();
        auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);
        if (!FIELD->IsInside(tiledCursorPos))
            return;

        //対象がクリックされているかチェック
        auto targets = FIELD->GetTiledObjects(tiledCursorPos);

        //タイル区切りで何も見つからないなら画像区切りで探す
        if (targets.size() == 0)
            targets = std::move(OBJECT_MGR->GetContainedObjects<TiledObject>(cursorPos));

        //自分がクリックされたら
        if (_monster != nullptr) {
            if (tiledCursorPos == _monster->GetTilePos())
            {
                if (_monster->IsEnable())
                {

                    TiledVector::Direction d = _monster->GetDirection();

                    switch (d)
                    {
                    case TiledVector::LEFT:
                        d = TiledVector::BACK;
                        break;
                    case TiledVector::FORWARD:
                        d = TiledVector::LEFT;
                        break;
                    case TiledVector::RIGHT:
                        d = TiledVector::FORWARD;
                        break;
                    case TiledVector::BACK:
                        d = TiledVector::RIGHT;
                        break;
                    default:
                        break;
                    }

                    _monster->SetDirection(d);

                    return;
                }
            }

            //自分以外を右クリックしたら選択解除
            _monster = nullptr;

        }
    }


}


void MonsterController::Draw()
{
    if (_monster == nullptr)
        return;

    if (!_monster->IsEnable())
        return;

    auto worldTilePos = _monster->GetTilePos().GetWorldPos();
    Debug::DrawRectWithSize(worldTilePos, Vector2D(TILE_SIZE, TILE_SIZE),
        Color4(0.0, 1.0, 0.0, 0.15), true);

    _monster->DrawTargetMarker();
}


void MonsterController::SetControlingMonster(Monster* monster)
{
    if (monster == _monster)
        return;

    if (_monster != nullptr)
        _monster->ReleaseMonster();

    //その魔物を選択状態に
    _monster = monster;
    _monster->PickMonster();
}


//魔物の選択
void MonsterController::SelectMonster(const Vector2D cursorPos)
{
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);

    //対象がクリックされているかチェック
    auto target = FIELD->GetTiledObject<Monster>(tiledCursorPos);

    //タイル区切りで何も見つからないなら画像区切りで探す
    if (target == nullptr)
        target = std::move(OBJECT_MGR->GetContainedObject<Monster>(cursorPos));

    //本当に何もないところなら終了
    if (target == nullptr)
        return;

    SetControlingMonster(target);
}

//魔物の操作
void MonsterController::ControlMonster(const Vector2D cursorPos)
{
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);

    //対象がクリックされているかチェック
    auto targets = FIELD->GetTiledObjects(tiledCursorPos);

    //タイル区切りで何も見つからないなら画像区切りで探す
    if (targets.size() == 0)
        targets = std::move(OBJECT_MGR->GetContainedObjects<TiledObject>(cursorPos));

    //本当に何もないところなら終了
    if (targets.size() == 0)
    {
        _monster->SetTarget(tiledCursorPos);
        return;
    }

    //自分がクリックされたら
    if (tiledCursorPos == _monster->GetTilePos())
    {
        if (_monster->IsEnable())
        {
            //選択を解除
            //_monster = nullptr;
            return;
        }
    }

    //何かあったなら
    for (auto target : targets)
    {
        //他の仲間がクリックされた
        if (target->GetType() == TiledObject::Type::MONSTER)
        {
            //他の仲間を選択
            auto monster = dynamic_cast<Monster*>(target);
            //その魔物を選択状態に
            _monster = monster;
            return;
        }
    }
    for (auto target : targets)
    {
        //魔法陣は
        if (target->GetType() == TiledObject::Type::MAGIC_SQUARE)
        {
            //他自分を召喚したものでなければクリックできない
            auto magicSquare = dynamic_cast<MagicSquare*>(target);
            if (!magicSquare->IsOwner(*_monster))
                return;
        }
    }
    for (auto target : targets)
    {
        //敵を選択したら
        if (target->GetType() == TiledObject::Type::ENEMY
            && target->IsEnable())
        {
            //敵を追跡
            _monster->SetTarget(target);
            return;
        }
    }

    //ここまで抜けたらモンスターの操作に影響するものは無いことになる.
    //モンスターをクリックした位置まで移動させる
    _monster->SetTarget(tiledCursorPos);
}
