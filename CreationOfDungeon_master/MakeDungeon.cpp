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
#include "cd_666s/TilebaseAI/Trap.h"

//#include "SettingBowgun.h"

#include <assert.h>

MakeDungeon::MakeDungeon()
{
}

MakeDungeon::MakeDungeon(std::string stage_num)
    : _stage_num(stage_num)
    , _mainsFrame("resourse/graph/ui/main_window.png", Vector2D(20, 20))
    , _background("resourse/graph/background/background.png", Vector2D(0, 7600))
    , _windowBackground("resourse/graph/ui/main_window_background1.png", Vector2D(28, 28))
{
    //�Ȃ���Sprite::Priority::UI(100)�ł͕`�悳�ꂸ�@�Ȃ��H
    _mainsFrame.SetPriority(101);
    _background.SetPriority(Sprite::Priority::BACKGROUND);
    _windowBackground.SetPriority(static_cast<int>(Sprite::Priority::BACKGROUND) + 1);
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

    //_monsters.Update();

    for (auto obj : OBJECT_MGR->_objects) {
        if (obj != nullptr) {
            //if (MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L)) {
            //obj->Update();
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
    
    //�^�C���̑傫����ǂݍ���
    std::string fileName = "csv/StageData/tilesize.csv";
    std::vector<std::string> tileInfoArray;
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, tileInfoArray);
    LoadTileSize(_stage_num, tileInfoArray);

    std::vector<std::string> _stageArray;
    //�t�B�[���h�̑�{�ƂȂ�f�[�^��ǂݍ���
    std::string filename = "csv/StageData/";
    filename += (file_name + ".csv");
    
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

    //FIELD->Init(fieldSizeH, fieldSizeV);

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

    /*�ݒu�I�u�W�F�N�g�����[�h���鏈�����K�v*/
    
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
    FIELD->SetFieldType(TiledVector(countX, countY), typeName);


    auto& _objs = OBJECT_MGR->_objects;
    
    if (typeName.find("9#") != std::string::npos)
    {
        Trap::CreateTrap(typeName, countX, countY, _objs);
        return;
    }

    if (typeName.find("2&") != std::string::npos)
    {
        LoadItem(typeName, countX, countY, _objs);
        return;
    }

    if (typeName.find("200") != std::string::npos)
    {
        if (_start == nullptr)
        {
            _start = std::make_shared<StartPoint>(TiledVector(countX, countY));
            _objs.push_back(_start);
        }
        return;
    }

    if (typeName.find("100") != std::string::npos)
    {
        if (_goal == nullptr)
        {
            _goal = std::make_shared<Goal>(TiledVector(countX, countY), _monsters);
            _objs.push_back(_goal);
        }
        return;
    }

    if (typeName.find("6") != std::string::npos)
    {
        _objs.push_back(std::make_shared<River>(TiledVector(countX, countY)));
        return;
    }

    if (typeName.find("1") != std::string::npos)
    {
        _objs.push_back(std::make_shared<Obstacle>(TiledVector(countX, countY)));
        return;
    }

    if (typeName == "0")
        return;


}



void MakeDungeon::LoadTileSize(std::string stageName, std::vector<std::string>& rawData)
{
    auto stageNum = std::stoi(stageName);
    auto tileSize = rawData[stageNum * 2 - 1];

    if (tileSize == "large")
        TILE_SIZE = 48;
    else if (tileSize == "midium")
        TILE_SIZE = 40;
    else
        TILE_SIZE = 32;
}



