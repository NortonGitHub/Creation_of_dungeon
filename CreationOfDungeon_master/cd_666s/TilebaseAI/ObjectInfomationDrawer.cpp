#include "ObjectInformationDrawer.h"
#include "Character.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"
#include "TileField.h"
#include "../Resources/ResourceManager.h"
#include "../InputManager/InputManager.h"
#include "../DebugDraw.h"

ObjectInformationDrawer::ObjectInformationDrawer(const TiledObjectDictionary& iconDictionary)
: _character1(nullptr)
, _character2(nullptr)
, _thumbnail1(iconDictionary, { 920, 140 })
, _thumbnail2(iconDictionary, { 920, 430 })
, _selectSE("sound/decide.wav")
{
    Init();
}


ObjectInformationDrawer::~ObjectInformationDrawer()
{
    Clear();
}


void ObjectInformationDrawer::Clear()
{
    _character1 = nullptr;
    _character2 = nullptr;

    _thumbnail1.Clear();
    _thumbnail2.Clear();
}


void ObjectInformationDrawer::Init()
{
    _character1 = nullptr;
    _character2 = nullptr;

    _thumbnail1.Init();
    _thumbnail2.Init();
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
        targets = std::move(OBJECT_MGR->GetContainedObjects<TiledObject>(cursorPos));
    
    //本当に何もないところなら終了
    if (targets.size() == 0)
        return;

    //先にバトル中かどうか確認
    for (auto target : targets)
    {
        //バトルをクリックしたら両方設置
        if (target->GetType() == TiledObject::Type::BATTLE)
        {
            _selectSE.Play();
            auto battle = dynamic_cast<BattlingTile*>(target);
            auto enemy = battle->GetEmemy();
            auto monster = battle->GetMonster();
            if (enemy != nullptr && monster != nullptr)
                SetCharacter(monster, enemy);

            return;
        }
    }

    for (auto target : targets)
    {
        //魔物や敵をクリックしたら
        if (target->GetType() == TiledObject::Type::MONSTER
            || target->GetType() == TiledObject::Type::ENEMY)
        {
            auto chara = dynamic_cast<Character*>(target);
            if (chara != nullptr && chara->IsEnable())
            {
                _selectSE.Play();
                SetCharacter(chara);
            }
            return;
        }
    }
}


void ObjectInformationDrawer::Update()
{
    SelectObject();
    
    if (_character1 != nullptr)
    {
        if (!_character1->IsAlive() || !_character1->IsEnable())
            _character1 = nullptr;
    }
    if (_character2 != nullptr)
    {
        if (!_character2->IsAlive() || !_character2->IsEnable())
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
    _thumbnail1.SetCharacter(_character1);
    _thumbnail2.SetCharacter(_character2);

    _thumbnail1.Draw();
    _thumbnail2.Draw();
}