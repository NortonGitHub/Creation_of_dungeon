#include "MakeDungeon.h"

#include "cd_666s\TilebaseAI\TiledObjectMnager.h"
#include "cd_666s/TilebaseAI/TileField.h"
#include "cd_666s\Resources\AllResourceManager.h"
#include "cd_666s/Render/RenderManager.h"
#include "cd_666s\Utility\CSVReader.h"

#include "cd_666s/TilebaseAI/TileField.h"
#include "cd_666s/TilebaseAI/River.h"
#include "cd_666s/TilebaseAI/Obstacle.h"
#include "cd_666s/TilebaseAI/EnemysItem.h"
#include "cd_666s/TilebaseAI/Monster.h"
//#include "cd_666s/TilebaseAI/Goal.h"
//#include "cd_666s/TilebaseAI/StartPoint.h"

#include "SettingBowgun.h"

#include <assert.h>

MakeDungeon::MakeDungeon()
{
}

MakeDungeon::MakeDungeon(std::string stage_num)
    : _stage_num(stage_num)
{
}


MakeDungeon::~MakeDungeon()
{
    OBJECT_MGR->Clear();
    _start = nullptr;
    _goal = nullptr;
    FIELD->Clear();

    RESOURCE_TABLE->Refresh();

    OBJECT_MGR->Refresh();
}

void MakeDungeon::Update()
{

    _monsters.Update();

    for (auto obj : OBJECT_MGR->_objects) {
        if (obj != nullptr) {
            //if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) {
            obj->Update();
            //}
        }
    }
}

void MakeDungeon::Draw()
{
    FIELD->Draw();
    for (auto obj : OBJECT_MGR->_objects) {
        if (obj != nullptr)
            obj->Draw();
    }
}

void MakeDungeon::Init(std::string file_name)
{
    std::vector<std::string> _stageArray;
    //フィールドの大本となるデータを読み込む
    std::string filename = "csv/StageData/";
    filename += (file_name + ".csv");
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + filename, _stageArray);
    auto fieldSizeH = reader.GetLineSize(filename, 0);
    auto fieldSizeV = reader.GetLineNum(filename);
    FIELD->Init(fieldSizeH, fieldSizeV);

    int countX = 0;
    int countY = 0;
    auto& _objs = OBJECT_MGR->_objects;

    filename = "csv/StageData/monsters";
    filename += (_stage_num + ".csv");
    Monster::LoadMonsters(_objs, _monsters, filename);

    FIELD->Init(fieldSizeH, fieldSizeV);

    for (auto data : _stageArray) {
        GenerateObject(data, countX, countY);

        countX++;

        if (countX == fieldSizeH) {
            countX = 0;
            countY++;
            if (countY == fieldSizeV) {
                break;
            }
        }
    }

    /*設置オブジェクトをロードする処理が必要*/

    _monsters.Update();

    FIELD->Setup();

    OBJECT_MGR->Refresh();

    for (auto obj : _objs)
    {
        if (obj.get() != nullptr)
            obj->Init();
    }
    _selectingObj = "NONE";
}

void MakeDungeon::PickupObject()
{

}

void MakeDungeon::GenerateObject(std::string typeName, int countX, int countY)
{
    FIELD->SetRawNumber(TiledVector(countX, countY), stoi(typeName));

    auto& _objs = OBJECT_MGR->_objects;
    switch (stoi(typeName))
    {
    case 0:
        return;

    case 1:
        _objs.push_back(std::make_shared<Obstacle>(TiledVector(countX, countY)));
        return;

    case 2:
        _objs.push_back(std::make_shared<EnemysItem>(TiledVector(countX, countY)));
        return;

    case 6:
        _objs.push_back(std::make_shared<River>(TiledVector(countX, countY)));
        return;

    case 100:
        if (_goal == nullptr)
        {
            _goal = std::make_shared<Goal>(TiledVector(countX, countY), _monsters);
            _objs.push_back(_goal);
        }
        return;

    case 200:
        if (_start == nullptr)
        {
            _start = std::make_shared<StartPoint>(TiledVector(countX, countY));
            _objs.push_back(_start);
        }
        return;

    case 301:
        _objs.push_back(std::make_shared<SettingBowgun>(TiledVector(countX, countY)));
        return;
    }
}