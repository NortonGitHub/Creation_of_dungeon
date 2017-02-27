#include "SettingBowgun.h"
#include "cd_666s/InputManager/InputManager.h"
#include "cd_666s/TilebaseAI/TileField.h"
#include "cd_666s/TilebaseAI/TiledObjectMnager.h"

SettingBowgun::SettingBowgun(TiledVector tilePos) : TiledObject(tilePos),_name("bowgun"){
}

SettingBowgun::~SettingBowgun(){
}

void SettingBowgun::Init()
{
}

void SettingBowgun::Interact(Character & character)
{
}

bool SettingBowgun::IsOverwritable(TiledObject * overwriter)
{
    return false;
}

void SettingBowgun::OnClicked()
{
}

void SettingBowgun::Update()
{

    double _x = MOUSE->GetCursorPos()._x;
    double _y = MOUSE->GetCursorPos()._y;

    if(MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)){
        auto tiledCursorPos = TiledVector::ConvertToTiledPos(MOUSE->GetCursorPos());
        if (!FIELD->IsInside(tiledCursorPos))
            return;

        //自分の位置がクリックされていなければ終了
        if (tiledCursorPos != GetTilePos())
            return;


    }
}

void SettingBowgun::Draw()
{
}
