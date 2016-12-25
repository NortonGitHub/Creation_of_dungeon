#include "ObjectInformationDrawer.h"
#include "Character.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"
#include "TileField.h"
#include "../InputManager/InputManager.h"
#include "../DebugDraw.h"

ObjectInformationDrawer::ObjectInformationDrawer()
: _character1(nullptr)
, _character2(nullptr)
{}


ObjectInformationDrawer::~ObjectInformationDrawer()
{}


void ObjectInformationDrawer::Init()
{
    _character1 = nullptr;
    _character2 = nullptr;
}


void ObjectInformationDrawer::SetCharacter(Character *chara)
{
    if (chara == _character1 || chara == _character2)
        return;
        
    //1�Ԗڂɏ�񂪂�������
    if (_character1 != nullptr)
    {
        //2�Ԗڂɏ�񂪂Ȃ��Ȃ�2�Ԃ�
        if (_character2 == nullptr)
        {
            _character2 = chara;
            return;
        }

        //�����łȂ��Ȃ牟���o��
        _character1 = chara;
        _character2 = _character1;
        return;
    }
    
    //�Ȃ�������1�Ԃɏ����Z�b�g
    _character1 = chara;
}


void ObjectInformationDrawer::SetCharacter(Character *chara, Character *chara2)
{
    _character1 = chara;
    _character2 = chara2;
}


void ObjectInformationDrawer::SelectObject()
{
    if (!MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
        return;
    
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
        //�o�g�����N���b�N�����痼���ݒu
        if (target->GetType() == TiledObject::Type::BATTLE)
        {
            auto battle = dynamic_cast<BattlingTile*>(target);
            _character1 = &battle->_monster;
            _character2 = &battle->_enemy;
        }
        
        //�������N���b�N������
        if (target->GetType() == TiledObject::Type::MONSTER
            || target->GetType() == TiledObject::Type::ENEMY)
        {
            auto chara = dynamic_cast<Character*>(target);
            if (chara != nullptr)
                SetCharacter(chara);
        }
    }
}


void ObjectInformationDrawer::Update()
{
    SelectObject();
    
    if (_character1 != nullptr)
    {
        if (!_character1->IsEnable() || !_character1->IsAlive())
            _character1 = nullptr;
    }
    if (_character2 != nullptr)
    {
        if (!_character2->IsEnable() || !_character2->IsAlive())
            _character2 = nullptr;
    }
    
    //1�̖ڂ��I������Ă��邩�����Ă�����I��
    if (_character1 != nullptr)
        return;
    
    //2�̖ڂ��I������ĂȂ��������ĂȂ��Ȃ�I��
    if (_character2 == nullptr)
        return;
        
    //�����܂Ŕ�������2�̖ڂ��������Ă���̂�
    //����1�̖ڂ̕��֋l�ߍ���
    _character1 = _character2;
    _character2 = nullptr;
}


void ObjectInformationDrawer::Draw()
{
    if (_character1 != nullptr)
        DrawCharactersInformation(_character1, Vector2D(920, 140));
    
    if (_character2 != nullptr)
        DrawCharactersInformation(_character2, Vector2D(920, 430));
}


void ObjectInformationDrawer::DrawCharactersInformation(Character* chara, Vector2D pos)
{
//    Character::BattleParameter param = chara->GetBattleParameter();
    const Character::BattleParameter& param = chara->_battleParameter;

    auto color = chara->GetType() == (TiledObject::Type::ENEMY) ? Color4(1.0, 0.5, 0.75, 1.0) : Color4(0.5, 0.75, 1.0, 1.0);

    //�h��Ԃ�
    Debug::DrawRectWithSize(pos, Vector2D(340, 270), color, true);
    
    //�g��
    Debug::DrawRectWithSize(pos, Vector2D(340, 270), ColorPalette::WHITE4, false);
    
    //�O���t�B�b�N�\��
    Debug::DrawRectWithSize(pos + Vector2D(120, 20), Vector2D(100, 100), ColorPalette::BLACK4, true);
    Debug::DrawRectWithSize(pos + Vector2D(120, 20), Vector2D(100, 100), ColorPalette::WHITE4, false);
    
    //�e��p�����[�^�`��
    std::string paramStr = "HP : ";
    paramStr += std::to_string(param._hp);
    paramStr += " / ";
    paramStr += std::to_string(chara->_maxHP);
    Debug::DrawString(pos + Vector2D(110, 130), paramStr);
    
    paramStr = "ATK : ";
    paramStr += std::to_string(param._attack);
    Debug::DrawString(pos + Vector2D(90, 170), paramStr);
    
    paramStr = "DEF : ";
    paramStr += std::to_string(param._defence);
    Debug::DrawString(pos + Vector2D(190, 170), paramStr);

    paramStr = "MATK : ";
    paramStr += std::to_string(param._attack);
    Debug::DrawString(pos + Vector2D(90, 200), paramStr);

    paramStr = "MDEF : ";
    paramStr += std::to_string(param._defence);
    Debug::DrawString(pos + Vector2D(180, 200), paramStr);


    paramStr = "SPD : ";
    paramStr += std::to_string(param._speed);
    Debug::DrawString(pos  + Vector2D(130, 230), paramStr);
}