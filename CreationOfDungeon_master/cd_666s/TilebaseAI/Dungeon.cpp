#include "Dungeon.h"
#include "../InputManager/InputManager.h"
#include "../Render/RenderManager.h"
#include "../Resources/AllResourceManager.h"
#include "../DebugDraw.h"
#include "../Utility/CSVReader.h"

#include "TileField.h"
#include "Enemy.h"
#include "Monster.h"
#include "Obstacle.h"
#include "River.h"
#include "EnemysItem.h"
#include "Goal.h"
#include "TiledObjectMnager.h"
#include "StartPoint.h"
#include "Trap.h"

#include <assert.h>


#include "../../MoneyManager.h"

Dungeon::Dungeon(std::string stageName)
    : _permitivePassedNum(2)
    , _stageName(stageName)
    , _goal(nullptr)
    , _start(nullptr)
    , _mainsFrame("resourse/graph/ui/main_window.png", Vector2D(20, 20))
    , _background("resourse/graph/background/background.png", Vector2D(0, 7600))
    , _windowBackground("resourse/graph/ui/main_window_background1.png", Vector2D(28, 28))
    , _waveInfomartionBoard("resourse/graph/ui/enemyinformation.png", Vector2D(754, 248))
    , _infoDrawer(_dictionary)
    , _intruderInformation(_dictionary)
    , _intrudeLastCharacter(false)
{

    _windowBackground.Load("resourse/graph/ui/main_window_background" + _stageName + ".png");
    _windowBackground.SetPosition(Vector2D(28, 28));


    _mainsFrame.SetPriority(Sprite::Priority::UI);
    _background.SetPriority(Sprite::Priority::BACKGROUND);
    _windowBackground.SetPriority(static_cast<int>(Sprite::Priority::BACKGROUND) + 1);
    _waveInfomartionBoard.SetPriority(Sprite::Priority::UI);
}


Dungeon::~Dungeon()
{
    Clear();
    OBJECT_MGR->Refresh();
}


void Dungeon::Init()
{
    _controller.Init();
    _infoDrawer.Init();

    _messageReciever.Init();
    LoadMessage(_stageName);

    //�X�e�[�W����
    std::vector<std::string> dataArray;
    CSVReader reader;
    
    //�E�F�[�u�̏���ǂݍ���
    std::string fileName = "csv/StageData/wave";
    fileName += (_stageName + ".csv");
    std::vector<std::string> waveInfoArray;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, waveInfoArray, 1);
    auto waveInterval = std::stoi(waveInfoArray[0]);
    _timer.InitWithSetup(waveInterval);
    _permitivePassedNum = std::stoi(waveInfoArray[1]);
    
    //�^�C���̑傫����ǂݍ���
    fileName = "csv/StageData/tilesize.csv";
    std::vector<std::string> tileInfoArray;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, tileInfoArray);
    LoadTileSize(_stageName, tileInfoArray);

    //�t�B�[���h�̃T�C�Y��ǂݍ���
    fileName = "csv/StageData/map";
    fileName += (_stageName + ".csv");
    auto fieldSizeH = reader.GetLineSize(fileName, 0);
    auto fieldSizeV = reader.GetLineNum(fileName);
    
    //�t�B�[���h�̃f�[�^��ǂݍ���
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray);
    int countX = 0;
    int countY = 0;
    FIELD->Init(fieldSizeH, fieldSizeV);

    //�I�u�W�F�N�g��ǂݍ���
    auto& _objs = OBJECT_MGR->_objects;
    for (auto data : dataArray)
    {
        //�󂯎�����f�[�^��ϊ��\�����Ƃɕϊ�
        GenerateObject(data, countX, countY);
        
        //���̃}�b�v�ԍ��܂�
        countX++;
        if (countX == fieldSizeH)
        {
            countX = 0;
            countY++;
            
            if (countY == fieldSizeV)
                break;
        }
    }
    
    assert( (_goal != nullptr) && (_start != nullptr) && "Cannot Read Start and Goal");
    
    //�N���ʒu��ݒ�
    _intruderInformation.InitWithSetup(_start);

    //�L�������������[�h
    fileName = "csv/StageData/enemys";
    fileName += (_stageName + ".csv");
    Enemy::LoadEnemys(_objs, *_start, *_goal, _enemys, fileName);

    fileName = "csv/StageData/monsters";
    fileName += (_stageName + ".csv");
    Monster::LoadMonsters(_objs, _monsters, fileName);
    
    FIELD->Setup();

    _monsters.Update();
    _enemys.Update();
    OBJECT_MGR->Refresh();
    
    for (auto obj : _objs)
    {
        if (obj.get() != nullptr)
            obj->Init();
    }
}


void Dungeon::GenerateObject(std::string typeName, int countX, int countY)
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
            _start = std::make_shared<StartPoint>(TiledVector(countX, countY), _messageReciever);
            _objs.push_back(_start);
        }
        return;
    }

    if (typeName.find("100") != std::string::npos)
    {
        if (_goal == nullptr)
        {
            _goal = std::make_shared<Goal>(TiledVector(countX, countY), _monsters, _messageReciever, _permitivePassedNum);
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


void Dungeon::Clear()
{
    _infoDrawer.Clear();

    OBJECT_MGR->Clear();
    _start = nullptr;
    _goal = nullptr;
    FIELD->Clear();

    RESOURCE_TABLE->Refresh();
}


bool Dungeon::HasClear()
{
    //WAVE��ς���������N���A
    if (_timer.HasTimeUp())
        return true;
    
    //WAVE���̓G��S�ł�������N���A
    if (Enemy::HasWipeOuted())
        return true;
    
    //�Ō�̓G��|������N���A
    if (_start->GetTimeUnitlNext() == StartPoint::NobodyIntruder()
        && _enemys.GetColleagues() == 0
        && !HasGameOver())
        return true;

    return false;
}


bool Dungeon::HasGameOver()
{
    auto passedNum = _goal->GetPassedNum();
    if (_permitivePassedNum < passedNum)
        return true;
        
    return false;
}


void Dungeon::Update()
{
    //���b�Z�[�W�X�V
    UpdateSecretary();

    _timer.Update();

    //���ԍX�V
    _monsters.Update();
    _enemys.Update();
    
    //�{�����X�V
    _controller.Update();

    for (auto obj : OBJECT_MGR->_objects)
    {
        if (obj != nullptr)
            obj->Update();
    }

    clsDx();
    printfDx("%d", MoneyManager::getInstance()->getMoney());

}


void Dungeon::Draw()
{
    //���ԂɂȂ����珉����
    if (_timer.HasTimeUp())
        return;

    FIELD->Draw();
    for (auto obj : OBJECT_MGR->_objects)
    {
        if (obj != nullptr)
            obj->Draw();
    }
    
    _infoDrawer.Update();
    _infoDrawer.Draw();
    _controller.Draw();
    
    OBJECT_MGR->Refresh();


    //���b�Z�[�W�E�B���h�E�X�V
    _messageReciever.Update();
    _messageReciever.Draw();

    //�X�e�[�W���\��
    Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), Color4(0.5, 0.65, 0.85, 1.0), true);
    Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), ColorPalette::WHITE4, false);
    Debug::DrawString(Vector2D(1010, 64), "���A�_���W���� ����" + _stageName);

    //�c�莞�ԕ\��
    _timer.Draw();

    //�m���}�\��
    std::string passed = "MISS:";
    Debug::DrawString(_waveInfomartionBoard.GetPosition() + Vector2D(20, 85), passed);
    passed = std::to_string(_goal->GetPassedNum());
    passed += "/";
    passed += std::to_string(_permitivePassedNum);
    Debug::DrawString(_waveInfomartionBoard.GetPosition() + Vector2D(50, 105), passed);

    //�N���ҏ��\��
    _intruderInformation.Draw();
}


void Dungeon::LoadMessage(std::string stageName)
{
    int messageNum = 0;
    if (stageName == "1")
        messageNum = 1;
    else if (stageName == "2")
        messageNum = 2;
    else if (stageName == "3")
        messageNum = 3;

    std::string filePath = "csv/talkData/stage";
    filePath += stageName;
    filePath += "/";
    //_dungeonMessage.insert(std::make_pair("missed", _messageReciever._processer.CreateTalkData("csv/talkData/missed.csv", Talk_Type::nomal)));
    _dungeonMessage.insert(std::make_pair("start", _messageReciever._processer.CreateTalkData(filePath + "0_secretary_start.csv", Talk_Type::nomal)));
    _dungeonMessage.insert(std::make_pair("middle", _messageReciever._processer.CreateTalkData(filePath + "1_secretary_middle.csv", Talk_Type::nomal)));

    if (messageNum != 3)
    {
        _dungeonMessage.insert(std::make_pair("last", _messageReciever._processer.CreateTalkData(filePath + "2_secretary_last.csv", Talk_Type::nomal)));
    }
    else
    {
        _dungeonMessage.insert(std::make_pair("blaver", _messageReciever._processer.CreateTalkData(filePath + "3_blaver_appeared.csv", Talk_Type::nomal)));
        _dungeonMessage.insert(std::make_pair("last", _messageReciever._processer.CreateTalkData(filePath + "2_secretary_blaverAppeared.csv", Talk_Type::nomal)));
    }
}


void Dungeon::UpdateSecretary()
{
    auto timeRatio = _timer.GetTimeRatio();

    if (timeRatio == 0)
    {
        _messageReciever.Recieve(_dungeonMessage.at("start"));
        return;
    }

    if (timeRatio == 0.5)
    {
        _messageReciever.Recieve(_dungeonMessage.at("middle"));
        return;
    }

    if (_intrudeLastCharacter)
        return;

    if (_stageName == "1")
    {
        if ( (_timer.GetCount() / 60) == 40)
        {
            _messageReciever.Recieve(_dungeonMessage.at("last"));
            _intrudeLastCharacter = true;
            return;
        }
    }
    else if (_stageName == "2")
    {
        if ((_timer.GetCount() / 60) == 50)
        {
            _messageReciever.Recieve(_dungeonMessage.at("last"));
            _intrudeLastCharacter = true;
            return;
        }
    }
    else
    {
        if (_start->GetTimeUnitlNext() == -1)
        {
            _messageReciever.Recieve(_dungeonMessage.at("last"));
            _messageReciever.Recieve(_dungeonMessage.at("blaver"));
            _intrudeLastCharacter = true;
        }
    }
}