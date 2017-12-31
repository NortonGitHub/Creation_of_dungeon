#include "MakeDungeon.h"

#include "cd_666s\TilebaseAI\TiledObjectMnager.h"
#include "cd_666s/TilebaseAI/TileField.h"
#include "cd_666s\Resources\AllResourceManager.h"
#include "cd_666s/Render/RenderManager.h"
#include "cd_666s\Utility\CSVReader.h"

#include "cd_666s/TilebaseAI/TileField.h"
#include "cd_666s/TilebaseAI/River.h"
#include "cd_666s/TilebaseAI/Obstacle.h"
#include "cd_666s/TilebaseAI/WeakObstacle.h"
#include "cd_666s/TilebaseAI/EnemysItem.h"
#include "cd_666s/TilebaseAI/Monster.h"
#include "cd_666s/TilebaseAI/Bridge.h"
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
    , _mainsFrame("resource/graph/ui/main_window.png", Vector2D(20, 20))
    , _background("resource/graph/background/background.png", Vector2D(0, 7600))
    , _windowBackground("resource/graph/ui/main_window_background_cave.png", Vector2D(28, 28))
{

	auto b_pos = _stage_num.rfind('b');

	if (b_pos != std::string::npos) {
		_stage_num_a = _stage_num.substr(0, b_pos);
	}
	else {
		_stage_num_a = _stage_num;
	}

    _background.Load("resource/graph/background/background_cave.png");
    _background.SetPosition(Vector2D(0, 0));

    _windowBackground.Load("resource/graph/ui/main_window_background_cave.png");
    _windowBackground.SetPosition(Vector2D(28, 28));

    _mainsFrame.SetPriority(Sprite::Priority::UI);
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

    _messageReciever.Init();

	_messageReciever.DrawFalse();

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

	SetFieldType();

    for (auto data : _stageArray) {
        GenerateObject(data, countX, countY);

        //ft���n�`���Ȃ̂œn��
        FIELD->SetFieldType(TiledVector(countX, countY), fieldTypeStr);

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

	if (typeName.find("300") != std::string::npos)
	{
		_objs.push_back(std::make_shared<WeakObstacle>(TiledVector(countX, countY), typeName));
		return;
	}

	if (typeName.find("301") != std::string::npos)
	{
		_objs.push_back(std::make_shared<Bridge>(typeName, TiledVector(countX, countY)));
		return;
	}


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
            _start = std::make_shared<StartPoint>(TiledVector(countX, countY), _messageReciever);
            _objs.push_back(_start);
        }
        return;
    }

    if (typeName.find("100") != std::string::npos)
    {
        if (_goal == nullptr)
        {
            _goal = std::make_shared<Goal>(TiledVector(countX, countY), _monsters, _messageReciever, 99);
            _objs.push_back(_goal);
        }
        return;
    }

    if (typeName.find("6") != std::string::npos)
    {
		_objs.push_back(std::make_shared<River>(TiledVector(countX, countY), typeName));
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



TiledObject* MakeDungeon::GenerateAddObject(std::string typeName, int countX, int countY, Vector2D mousePos)
{
    FIELD->SetRawNumber(TiledVector(countX, countY), stoi(typeName));
    FIELD->SetFieldType(TiledVector(countX, countY), typeName);


    auto& _objs = OBJECT_MGR->_objects;

	if (typeName.find("300") != std::string::npos)
	{
		_objs.push_back(std::make_shared<WeakObstacle>(TiledVector(countX, countY), typeName));
		//��̃}�X�ɕ����̃I�u�W�F�N�g�͂Ȃ��̂ł���Ő��������I�u�W�F�N�g�̃|�C���^���Ƃ��͂�
		std::vector<TiledObject*> toTemp = FIELD->GetTiledObjects(TiledVector(countX, countY));
		TiledObject* to;
		if (!toTemp.empty()) {
			to = toTemp[0];
		}
		else {
			to = nullptr;
		}
		return to;
	}

	if (typeName.find("301") != std::string::npos)
	{
		_objs.push_back(std::make_shared<Bridge>(typeName, TiledVector(countX, countY)));
		//��̃}�X�ɕ����̃I�u�W�F�N�g�͂Ȃ��̂ł���Ő��������I�u�W�F�N�g�̃|�C���^���Ƃ��͂�
		std::vector<TiledObject*> toTemp = FIELD->GetTiledObjects(TiledVector(countX, countY));
		TiledObject* to;
		if (!toTemp.empty()) {
			to = toTemp[0];
		}
		else {
			to = nullptr;
		}
		return to;
	}

    if (typeName.find("9#") != std::string::npos)
    {
        Trap::CreateTrap(typeName, countX, countY, _objs);
        //��̃}�X�ɕ����̃I�u�W�F�N�g�͂Ȃ��̂ł���Ő��������I�u�W�F�N�g�̃|�C���^���Ƃ��͂�
        std::vector<TiledObject*> toTemp = FIELD->GetTiledObjects(TiledVector(countX, countY));
        TiledObject* to;
        if (!toTemp.empty()) {
            to = toTemp[0];
        }
        else {
            to = nullptr;
        }
        return to;
    }

    if (typeName.find("2&") != std::string::npos)
    {
        LoadItem(typeName, countX, countY, _objs);
        //��̃}�X�ɕ����̃I�u�W�F�N�g�͂Ȃ��̂ł���Ő��������I�u�W�F�N�g�̃|�C���^���Ƃ��͂�
        std::vector<TiledObject*> toTemp = FIELD->GetTiledObjects(TiledVector(countX, countY));
        TiledObject* to;
        if (!toTemp.empty()) {
            to = toTemp[0];
        }
        else {
            to = nullptr;
        }
        return to;
    }
    /*
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
    */
    if (typeName.find("6") != std::string::npos)
    {
		_objs.push_back(std::make_shared<River>(TiledVector(countX, countY), typeName));
        //��̃}�X�ɕ����̃I�u�W�F�N�g�͂Ȃ��̂ł���Ő��������I�u�W�F�N�g�̃|�C���^���Ƃ��͂�
        std::vector<TiledObject*> toTemp = FIELD->GetTiledObjects(TiledVector(countX, countY));
        TiledObject* to;
        if (!toTemp.empty()) {
            to = toTemp[0];
        }
        else {
            to = nullptr;
        }
        return to;
    }

    if (typeName.find("1") != std::string::npos)
    {
        _objs.push_back(std::make_shared<Obstacle>(TiledVector(countX, countY)));
        //��̃}�X�ɕ����̃I�u�W�F�N�g�͂Ȃ��̂ł���Ő��������I�u�W�F�N�g�̃|�C���^���Ƃ��͂�
        std::vector<TiledObject*> toTemp = FIELD->GetTiledObjects(TiledVector(countX, countY));
        TiledObject* to;
        if (!toTemp.empty()) {
            to = toTemp[0];
        }
        else {
            to = nullptr;
        }
        return to;
    }

    if (typeName == "0")
        return nullptr;

    

    return nullptr;

}

std::vector<TiledObject*> MakeDungeon::GenerateMonster(std::string fileName, TiledVector startPos, std::string* GenerateText, int level) {

	std::vector<TiledObject*> temp;
	temp.clear();
	
	if (level <= 0) {
		return temp;
	}

    auto& _objs = OBJECT_MGR->_objects;

	temp = Monster::GenerateMonster(_objs, _monsters, fileName, startPos, GenerateText, level);

    _monsters.Update();

    return temp;

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


std::shared_ptr<Goal> MakeDungeon::getGoal(){

    return _goal;

}

std::shared_ptr<StartPoint> MakeDungeon::getStart(){

    return _start;

}


void MakeDungeon::SetFieldType() {

	//�_���W�����̒n�`�̐ݒ�

	CSVReader reader;

	std::vector<std::string> FieldTypeArray;
	std::string fileName = "csv/StageData/DungeonType.csv";
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, FieldTypeArray, 2);

	int FieldTypeNum = stoi(FieldTypeArray[stoi(_stage_num_a) * 2 - 1]);

	switch (FieldTypeNum) {
	case 0:
		fieldTypeStr = "#CAV";
		_windowBackground.Load("resource/graph/ui/main_window_background_cave.png");
		_background.Load("resource/graph/background/background_cave.png");
		break;
	case 1:
		fieldTypeStr = "#FST";
		_windowBackground.Load("resource/graph/ui/main_window_background_forest.png");
		_background.Load("resource/graph/background/background_forest.jpg");
		break;
	case 2:
		fieldTypeStr = "#STN";
		_windowBackground.Load("resource/graph/ui/main_window_background_stone.png");
		_background.Load("resource/graph/background/background_stone.jpg");
		break;
	case 3:
		fieldTypeStr = "#TIM";
		_windowBackground.Load("resource/graph/ui/main_window_background_wood.png");
		_background.Load("resource/graph/background/background_wood.png");
		break;
	default:
		fieldTypeStr = "#CAV";
		_windowBackground.Load("resource/graph/ui/main_window_background_cave.png");
		_background.Load("resource/graph/background/background_cave.png");
		break;
	}
	_windowBackground.SetPosition(Vector2D(28, 28));
	_background.SetPosition(Vector2D(0, 0));

}


std::string MakeDungeon::GetFieldType() {
	return fieldTypeStr;
}

