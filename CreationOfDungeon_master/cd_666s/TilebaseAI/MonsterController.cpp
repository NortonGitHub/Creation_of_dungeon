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
    if (!MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
        return;
    
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(MOUSE->GetCursorPos());
    if (!FIELD->IsInside(tiledCursorPos))
        return;
    
    if (_monster == nullptr)
        SelectMonster();
    else
        ControlMonster();
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
    
    //���̖�����I����Ԃ�
    _monster = monster;
    _monster->PickMonster();
}


//�����̑I��
void MonsterController::SelectMonster()
{
    auto cursorPos = MOUSE->GetCursorPos();
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);
    
    //�Ώۂ��N���b�N����Ă��邩�`�F�b�N
    auto targets = FIELD->GetTiledObjects(tiledCursorPos);
    
    //�^�C����؂�ŉ���������Ȃ��Ȃ�摜��؂�ŒT��
    if (targets.size() == 0)
        targets = std::move(OBJECT_MGR->GetContainedObjects(cursorPos));
    
    //�{���ɉ����Ȃ��Ƃ���Ȃ�I��
    if (targets.size() == 0)
        return;
    
    for (auto target : targets)
    {
        //�������N���b�N������
        if (target->GetType() == TiledObject::Type::MONSTER)
        {
            auto monster = dynamic_cast<Monster*>(target);
            //if (monster->IsEnable())
                SetControlingMonster(monster);
        }
    }
}

//�����̑���
void MonsterController::ControlMonster()
{
    auto cursorPos = MOUSE->GetCursorPos();
    auto tiledCursorPos = TiledVector::ConvertToTiledPos(cursorPos);
    
    //�Ώۂ��N���b�N����Ă��邩�`�F�b�N
    auto targets = FIELD->GetTiledObjects(tiledCursorPos);

    //�^�C����؂�ŉ���������Ȃ��Ȃ�摜��؂�ŒT��
    if (targets.size() == 0)
        targets = std::move(OBJECT_MGR->GetContainedObjects(cursorPos));
    
    //�{���ɉ����Ȃ��Ƃ���Ȃ�I��
    if (targets.size() == 0)
    {
        _monster->SetTarget(tiledCursorPos);
        return;
    }

    //�������N���b�N���ꂽ��
    if (tiledCursorPos == _monster->GetTilePos())
    {
        if (_monster->IsEnable())
        {
            //�I��������
            _monster = nullptr;
            return;
        }
    }

    //�����������Ȃ�
    for (auto target : targets)
    {
        //���̒��Ԃ��N���b�N���ꂽ
        if (target->GetType() == TiledObject::Type::MONSTER)
        {
            //���̒��Ԃ�I��
            auto monster = dynamic_cast<Monster*>(target);
            //���̖�����I����Ԃ�
            _monster = monster;
            return;
        }
    }
    for (auto target : targets)
    {
        //���@�w��
        if (target->GetType() == TiledObject::Type::MAGIC_SQUARE)
        {
            //�������������������̂łȂ���΃N���b�N�ł��Ȃ�
            auto magicSquare = dynamic_cast<MagicSquare*>(target);
            if (!magicSquare->IsOwner(*_monster))
                return;
        }
    }
    for (auto target : targets)
    {
        //�G��I������
        if (target->GetType() == TiledObject::Type::ENEMY
            && target->IsEnable())
        {
            //�G��ǐ�
            _monster->SetTarget(target);
            return;
        }
    }

    if (_monster != nullptr)
        _monster->SetTarget(tiledCursorPos);
}