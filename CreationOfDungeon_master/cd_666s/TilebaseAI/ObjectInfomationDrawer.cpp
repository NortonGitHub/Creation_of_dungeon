#include "ObjectInformationDrawer.h"
#include "Character.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"
#include "TileField.h"
#include "../Resources/ResourceManager.h"
#include "../InputManager/InputManager.h"
#include "../DebugDraw.h"

ObjectInformationDrawer::ObjectInformationDrawer()
: _character1(nullptr)
, _character2(nullptr)
, _enemyThumbnail1(RESOURCE_TABLE->GetFolderPath() + "graph/enemy_thumbnail.png", Vector2D(920, 130))
, _enemyThumbnail2(RESOURCE_TABLE->GetFolderPath() + "graph/enemy_thumbnail.png", Vector2D(920, 420))
, _allyThumbnail1(RESOURCE_TABLE->GetFolderPath() + "graph/ally_thumbnail.png", Vector2D(920, 130))
, _allyThumbnail2(RESOURCE_TABLE->GetFolderPath() + "graph/ally_thumbnail.png", Vector2D(920, 420))
{
    _enemyThumbnail1.GetTexturePtr()->SetDisplayMode(false);
    _enemyThumbnail2.GetTexturePtr()->SetDisplayMode(false);
    _allyThumbnail1.GetTexturePtr()->SetDisplayMode(false);
    _allyThumbnail2.GetTexturePtr()->SetDisplayMode(false);

    _enemyThumbnail1.GetTexturePtr()->SetPriority(100);
    _enemyThumbnail2.GetTexturePtr()->SetPriority(100);
    _allyThumbnail1.GetTexturePtr()->SetPriority(100);
    _allyThumbnail2.GetTexturePtr()->SetPriority(100);
}


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
        
    //1番目に情報があったら
    if (_character1 != nullptr)
    {
        //2番目に情報がないなら2番に
        if (_character2 == nullptr)
        {
            _character2 = chara;
            return;
        }

        //そうでないなら押し出し
        _character2 = _character1;
        _character1 = chara;
        return;
    }
    
    //なかったら1番に情報をセット
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
    
    //対象がクリックされているかチェック
    auto targets = FIELD->GetTiledObjects(tiledCursorPos);
    
    //タイル区切りで何も見つからないなら画像区切りで探す
    if (targets.size() == 0)
        targets = std::move(OBJECT_MGR->GetContainedObjects(cursorPos));
    
    //本当に何もないところなら終了
    if (targets.size() == 0)
        return;
    
    for (auto target : targets)
    {
        //バトルをクリックしたら両方設置
        if (target->GetType() == TiledObject::Type::BATTLE)
        {
            auto battle = dynamic_cast<BattlingTile*>(target);
            _character1 = &battle->_monster;
            _character2 = &battle->_enemy;
            return;
        }
        
        //魔物をクリックしたら
        if (target->GetType() == TiledObject::Type::MONSTER
            || target->GetType() == TiledObject::Type::ENEMY)
        {
            auto chara = dynamic_cast<Character*>(target);
            if (chara != nullptr)
                SetCharacter(chara);

            return;
        }
    }
}


void ObjectInformationDrawer::Update()
{
    SelectObject();
    
    if (_character1 != nullptr)
    {
        if (!_character1->IsAlive())
            _character1 = nullptr;
    }
    if (_character2 != nullptr)
    {
        if (!_character2->IsAlive())
            _character2 = nullptr;
    }
    
    //1体目が選択されているか生きていたら終了
    if (_character1 != nullptr)
        return;
    
    //2体目が選択されてないか生きてないなら終了
    if (_character2 == nullptr)
        return;
        
    //ここまで抜けたら2体目だけ生きているので
    //情報を1体目の方へ詰め込む
    _character1 = _character2;
    _character2 = nullptr;
}


void ObjectInformationDrawer::Draw()
{
    if (_character1 != nullptr)
    {
        if (_character1->GetType() == TiledObject::Type::ENEMY)
        {
            _enemyThumbnail1.GetTexturePtr()->SetDisplayMode(true);
            _allyThumbnail1.GetTexturePtr()->SetDisplayMode(false);
        }
        else
        {
            _allyThumbnail1.GetTexturePtr()->SetDisplayMode(true);
            _enemyThumbnail1.GetTexturePtr()->SetDisplayMode(false);
        }

        DrawCharactersInformation(_character1, Vector2D(920, 140));
    }
    else
    {
        _enemyThumbnail1.GetTexturePtr()->SetDisplayMode(false);
        _allyThumbnail1.GetTexturePtr()->SetDisplayMode(false);
    }
    
    if (_character2 != nullptr)
    {
        if (_character2->GetType() == TiledObject::Type::ENEMY)
        {
            _enemyThumbnail2.GetTexturePtr()->SetDisplayMode(true);
            _allyThumbnail2.GetTexturePtr()->SetDisplayMode(false);
        }
        else
        {
            _allyThumbnail2.GetTexturePtr()->SetDisplayMode(true);
            _enemyThumbnail2.GetTexturePtr()->SetDisplayMode(false);
        }

        DrawCharactersInformation(_character2, Vector2D(920, 430));
    }
    else
    {
        _enemyThumbnail2.GetTexturePtr()->SetDisplayMode(false);
        _allyThumbnail2.GetTexturePtr()->SetDisplayMode(false);
    }
}


void ObjectInformationDrawer::DrawCharactersInformation(Character* chara, Vector2D pos)
{
//    Character::BattleParameter param = chara->GetBattleParameter();
    const Character::BattleParameter& param = chara->_battleParameter;

    auto color = (chara->GetType() == TiledObject::Type::ENEMY) ? ColorPalette::RED4 : ColorPalette::BLUE4;
    Vector2D hpOffset(110, 130);
    Debug::DrawString(pos + hpOffset, "HP");
    Debug::DrawRectWithSize(pos + hpOffset + Vector2D(24, 0), Vector2D(param._hp / double(chara->_maxHP) * 96, 12), color, true);
    Debug::DrawRectWithSize(pos + hpOffset + Vector2D(24, 0), Vector2D(96, 12), ColorPalette::BLACK4, false);

    std::string paramStr = "ATK : ";
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